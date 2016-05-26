#ifndef ASM_H
#define ASM_H

#include <stdint.h>

typedef enum {
    SKIP = 0, // skip line
    LD = 1, // load from mem to stack
    ST, // unload from stack into mem
    LDC, // load num into stack
    ADD, // add 2 numbers from stack
    SUB, // sub 2 numbers from stack
    CMP, // compare 2 numbers from stack
    JMP, // jump to label
    BR, // jump to label if we have nonzero number on the top
    RET // successfully exit
} instr_type;

typedef struct {
    instr_type type;
    int32_t arg;
    char* label;
} instr_t;

#endif // ASM_H
