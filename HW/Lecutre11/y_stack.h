// y_stack.h

#ifndef Y_STACK_H
#define Y_STACK_H

struct node {
    int data;
    struct node* prev_node;
};

struct y_stack {
    int count;
    struct node* data;
};

// Function declarations
void push(struct y_stack* stack, int value);
int pop(struct y_stack* stack);

#endif // Y_STACK_H