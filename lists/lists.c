#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

/**
* The last remark is unclear: if this means reimplementing the whole
* task without fake root, I don't agree it's necessary as
* rewriting many lines of code and additional checks are required in
* such case :/
**/

// This function tries to allocate memory and checks whether NULL is returned
void* alloc(size_t sz) {
    void* res = malloc(sz);
    if (res == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
        exit(1);
    }
    return res;
}

struct node {
    int value;
    node* next;
    node* last;
};

void append(node* root, int val) {
    node* tmp = (node*) alloc(sizeof(node));
    tmp->value = val;
    tmp->next = NULL;
    root->last->next = tmp;
    root->last = tmp;
}

void erase(node* root, int val) {
    node* cur = root;
    node* tmp = root;
    while (cur->next != NULL) {
        tmp = cur;
        cur = cur->next;
        if (cur->value == val) {
            tmp->next = cur->next;
            if (cur->next == NULL)
                tmp->last = tmp;
            else
                tmp->last = cur->next;
            free(cur);
            break;
        }
    }
}

void print(node* root) {
    node* cur = root;
    while (cur->next != NULL) {
        cur = cur->next;
        printf("%d ", cur->value);
    }
    printf("\n");
}

void clean(node* root) {
    node* cur = root;
    while (cur->next != NULL) {
        node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void add_cycle(node* root) {
    node* cur = root;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = root;
}

int check_cycle(node* root) {
    node* cur = root;
    node* tmp = root;
    char torch = 0, wasCycle = 0;
    for (;;) {
        if (torch) {
            if (cur->next != NULL)
                cur = cur->next;
            else
                break;
        } else {
            if (tmp->next != NULL && tmp->next->next != NULL)
                tmp = tmp->next->next;
            else
                break;
        }
        if (tmp == cur) {
            wasCycle = 1;
            break;
        }
        torch = !torch;
    }
    return wasCycle;
}

int main() {
    node* root = (node*) alloc(sizeof(node));
    root->next = NULL;
    root->last = root;
    char c;
    printf("Type the command (h for help)\n");
    for (;;) {
        do
            c = getchar();
        while (isspace(c));
        int val;
        switch (c) {
        case 'a':
            scanf("%d", &val);
            append(root, val);
            break;
        case 'r':
            scanf("%d", &val);
            erase(root, val);
            break;
        case 'p':
            print(root);
            break;
        case 'q':
            clean(root);
            return 0;
        case 'b': // add cycle
            add_cycle(root);
            break;
        case 'c': // check for cycles
            printf("%s\n", check_cycle(root) ? "Cyclic" : "Non-Cyclic");
            break;
        case 'h':
            printf("a x - Add x to the list\n");
            printf("r x - Erase first occurrence x from the list\n");
            printf("p   - Print the list content\n");
            printf("b   - Add cycle (break the list)\n");
            printf("c   - Check whether the list is cyclic\n");
            printf("q   - Quit\n");
            break;
        default:
            printf("Invalid command. Use h for help\n");
            break;
        }
    }
    return 0;   
}
