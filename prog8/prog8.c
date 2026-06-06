#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A structure to represent a stack (Peg)
struct Stack {
    int capacity;
    int top;
    int *array;
};

// Function to create a stack of given capacity
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is -1
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, int item) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
int pop(struct Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

// Function to implement the movement of a disk between two poles
void moveDisk(char fromPeg, char toPeg, int disk) {
    printf("Move disk %d from %c to %c\n", disk, fromPeg, toPeg);
}

// Function to implement legal movement between two poles
void moveDisksBetweenTwoPoles(struct Stack *src, struct Stack *dest, char s, char d) {
    int pole1TopDisk = pop(src);
    int pole2TopDisk = pop(dest);

    // When pole 1 is empty
    if (pole1TopDisk == -1) {
        push(src, pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    // When pole 2 is empty
    else if (pole2TopDisk == -1) {
        push(dest, pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
    // When top disk of pole 1 is greater than top disk of pole 2
    else if (pole1TopDisk > pole2TopDisk) {
        push(src, pole1TopDisk);
        push(src, pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    // When top disk of pole 1 is smaller than top disk of pole 2
    else {
        push(dest, pole2TopDisk);
        push(dest, pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
}

// Iterative Towers of Hanoi function
void towersOfHanoiIterative(int num_of_disks) {
    struct Stack *src, *aux, *dest;
    int total_num_of_moves = pow(2, num_of_disks) - 1;
    char s = 'A', a = 'B', d = 'C';

    // If number of disks is even, then interchange destination and auxiliary pole
    if (num_of_disks % 2 == 0) {
        char temp = d;
        d = a;
        a = temp;
    }

    // Create three stacks to represent the three poles
    src = createStack(num_of_disks);
    aux = createStack(num_of_disks);
    dest = createStack(num_of_disks);

    // Push larger disks to src stack first (bottom to top)
    for (int i = num_of_disks; i >= 1; i--) {
        push(src, i);
    }

    // Run the loop for total number of moves
    for (int i = 1; i <= total_num_of_moves; i++) {
        if (i % 3 == 1) {
            moveDisksBetweenTwoPoles(src, dest, s, d);
        } else if (i % 3 == 2) {
            moveDisksBetweenTwoPoles(src, aux, s, a);
        } else if (i % 3 == 0) {
            moveDisksBetweenTwoPoles(aux, dest, a, d);
        }
    }
    
    // Free allocated memory
    free(src->array); free(src);
    free(aux->array); free(aux);
    free(dest->array); free(dest);
}

int main() {
    int num_of_disks = 3;
    printf("Iterative Towers of Hanoi for %d disks:\n", num_of_disks);
    towersOfHanoiIterative(num_of_disks);
    return 0;
}