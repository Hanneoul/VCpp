#include "y_stack.h"
// y_stack.c

#include "y_stack.h"
#include <stdlib.h>

void push(struct y_stack* stack, int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->prev_node = stack->data;

    stack->data = new_node;
    stack->count++;
}

int pop(struct y_stack* stack) {
    if (stack->count == 0) {
        // Handle underflow (stack is empty)
        exit(EXIT_FAILURE);
    }

    int popped_value = stack->data->data;
    struct node* temp = stack->data;
    stack->data = stack->data->prev_node;

    free(temp);
    stack->count--;

    return popped_value;
}