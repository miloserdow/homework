#include <stdio.h>
#include <stdlib.h>
#include "stack.h"       

void stackInit(stack_t *stackP, int maxSize) {
    int32_t *newContents;

    newContents = (int32_t *)malloc(sizeof(int32_t) * maxSize);
    if (newContents == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    stackP->contents = newContents;
    stackP->maxSize = maxSize;
    stackP->top = -1;  // empty
}

void stackDestroy(stack_t *stackP) {
    free(stackP->contents);
    stackP->contents = NULL;
    stackP->maxSize = 0;
    stackP->top = -1;  // empty
}

void stackPush(stack_t *stackP, int32_t element) {
    if (stackIsFull(stackP)) {
        fprintf(stderr, "Can't push element on stack: stack is full.\n");
        exit(1);
    }

    // update top
    stackP->contents[++stackP->top] = element;
}

int32_t stackTop(stack_t *stackP) {
    if (stackIsEmpty(stackP)) {
        fprintf(stderr, "Can't stack top of empty stack");
        exit(1);
    }
    return stackP->contents[stackP->top];
}

int32_t stackPop(stack_t *stackP) {
    if (stackIsEmpty(stackP)) {
        fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
        exit(1);
    }
    return stackP->contents[stackP->top--];
}

int stackIsEmpty(stack_t *stackP) {
    return stackP->top < 0;
}

int stackIsFull(stack_t *stackP) {
    return stackP->top >= stackP->maxSize - 1;
}
