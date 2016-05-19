#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "hash_table.h"
#include "asm.h"

#define MX 262144
#define MX_INSTR 10000

int32_t* memory;
stack_t* st;
hashtable_t* labels;
instr_t* program;

void do_ld(int32_t addr);
void do_st(int32_t addr);
void do_ldc(int32_t num);
void do_add();
void do_sub();
void do_cmp();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./FakeASM <source file>");
        exit(1);
    }
    char* fname = argv[1];

    // Init phase
    memory = (int32_t*) malloc(sizeof(int32_t) * MX);
    if (memory == NULL) {
        fprintf(stderr, "allocation of memory array failed\n");
        exit(1);
    }
    st = (stack_t*) malloc(sizeof(stack_t));
    if (st == NULL) {
        fprintf(stderr, "allocation of stack_t ptr failed\n");
        exit(1);
    }
    stackInit(st, MX); // let's make it as big as MEM
    labels = init_table(MX_INSTR);
    program = (instr_t*) malloc(sizeof(instr_t) * MX_INSTR);
    
    // Program reading phase
    FILE* inp = fopen(fname, "r");
    if (inp == NULL) {
        fprintf(stderr, "file could not be opened for some reason\n");
        exit(1);
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int cnt = 0;
    while ((read = getline(&line, &len, inp)) != -1) {
        char* cut = strchr(line, ';');
        if (cut != NULL) *cut = '\0';
        char* m = strchr(line, ':');
        char* cur_label = 0;
        char* cur_instr = (char*) malloc(sizeof(char) * MX_INSTR);
        char* cur_arg = (char*) malloc(sizeof(char) * MX_INSTR);
        if (cur_instr == NULL || cur_arg == NULL)
            fprintf(stderr, "allocation for buffer failed\n");
        if (m == NULL)
            cur_label = 0;
        else {
            cur_label = line;
            cur_label[m - line] = '\0';
            set_value(labels, cur_label, cnt);
            line = m + 1;
        }
        sscanf(line, "%s %s\n", cur_instr, cur_arg);
        
        if (!strcmp(cur_instr, "ld")) {
            program[cnt].type = LD;
            program[cnt].arg = atoi(cur_arg);
        }
        else if (!strcmp(cur_instr, "st")) {
            program[cnt].type = ST;
            program[cnt].arg = atoi(cur_arg);
        }
        else if (!strcmp(cur_instr, "ldc")) {
            program[cnt].type = LDC;
            program[cnt].arg = atoi(cur_arg);
        }
        else if (!strcmp(cur_instr, "add")) {
            program[cnt].type = ADD;
        }
        else if (!strcmp(cur_instr, "sub")) {
            program[cnt].type = SUB;
        }
        else if (!strcmp(cur_instr, "cmp")) {
            program[cnt].type = CMP;
        }
        else if (!strcmp(cur_instr, "jmp") || !strcmp(cur_instr, "br")) {
            program[cnt].type = (!strcmp(cur_instr, "jmp") ? JMP : BR);
            program[cnt].label = (char*) malloc(sizeof(char) * (strlen(cur_arg) + 1));
            if (program[cnt].label == NULL) {
                fprintf(stderr, "allocation error\n");
                exit(1);
            }
            strcpy(program[cnt].label, cur_arg);
        }
        else if (!strcmp(cur_instr, "ret")) {
            program[cnt].type = RET;
        }
        else {
            int i = 0;
            for (i = 0; i < strlen(cur_instr); i++) {
                if (!isspace(cur_instr[i])) {
                    fprintf(stderr, "unrecognized command: %s\n", cur_instr);
                    exit(1);
                }
            }
            program[cnt].type = SKIP;
        }
        cnt++;
    }
    fclose(inp);

    int i;
    for (i = 0; i < cnt; i++) {
        if (program[i].type == JMP || program[i].type == BR) {
            program[i].arg = get_value(labels, program[i].label);
            free(program[i].label);
        }
    }
    // Execution phase
    int ip = 0x0;
    for (;;) {
        switch (program[ip].type) {
        case SKIP:
            break;
        case LD:
            do_ld(program[ip].arg);
            break;
        case ST:
            do_st(program[ip].arg);
            break;
        case LDC:
            do_ldc(program[ip].arg);
            break;
        case ADD:
            do_add();
            break;
        case SUB:
            do_sub();
            break;
        case CMP:
            do_cmp();
            break;
        case JMP:
            ip = (int) program[ip].arg - 1;
            break;
        case BR:
            if (stackTop(st))
                ip = (int) program[ip].arg - 1;
            break;
        case RET:
            printf("Program has finished\nStack: ");
            while (!stackIsEmpty(st))
                printf("%d ", stackPop(st));
            printf("\n");
            exit(0);
            break;
        default:
            fprintf(stderr, "Unknown error\n");
            exit(1);
            break;
        }
        ip++;
    }
    
    // Destroy phase
    free(program);
    delete_table(labels);
    stackDestroy(st);
    free(memory);
    return 0;
}

void do_ld(int32_t addr) {
    int32_t val = memory[addr];
    stackPush(st, val);
}

void do_st(int32_t addr) {
    int32_t val = stackPop(st);
    memory[addr] = val;
}

void do_ldc(int32_t num) {
    stackPush(st, num);
}

void do_add() {
    int32_t arg1 = stackPop(st), arg2 = stackPop(st);
    int32_t res = arg1 + arg2;
    stackPush(st, res);
}

void do_sub() {
    int32_t arg1 = stackPop(st), arg2 = stackPop(st);
    int32_t res = arg1 - arg2;
    stackPush(st, res);
}

void do_cmp() {
    int32_t arg1 = stackPop(st), arg2 = stackPop(st);
    int32_t res;
    if (arg1 > arg2)
        res = 1;
    else if (arg2 > arg1)
        res = -1;
    else
        res = 0;
    stackPush(st, res);
}
