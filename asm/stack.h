#ifndef STACK_H
#define STACK_H

typedef struct {
    int32_t *contents;
    int maxSize;
    int top;
} stack_t;

void     stackInit(stack_t *stackP, int maxSize);
void     stackDestroy(stack_t *stackP);
void     stackPush(stack_t *stackP, int32_t element);
int32_t  stackTop(stack_t *stackP);
int32_t  stackPop(stack_t *stackP);
int      stackIsEmpty(stack_t *stackP);
int      stackIsFull(stack_t *stackP);

#endif  // STACK_H
