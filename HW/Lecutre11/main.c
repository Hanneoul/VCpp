// main.c

#include "y_stack.h"
#include <stdio.h>

int main() {
    // Create a stack
    struct y_stack my_stack;
    my_stack.count = 0;
    my_stack.data = NULL;

    // Test push
    push(&my_stack, 1);
    push(&my_stack, 2);
    push(&my_stack, 3);

    // Test pop
    printf("Popped value: %d\n", pop(&my_stack));
    printf("Popped value: %d\n", pop(&my_stack));
    printf("Popped value: %d\n", pop(&my_stack));

    return 0;
}