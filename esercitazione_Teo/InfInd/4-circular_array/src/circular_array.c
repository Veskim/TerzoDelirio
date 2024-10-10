#include <stdio.h>
#include <stdlib.h>
#include "circular_array.h"

// max array dimension
#define MAX_SIZE 5

// static variable buffer
static char buffer[MAX_SIZE];
static int head = 0;
static int tail = 0;
static int currentSize = 0;

// Check Full Array?
static int isFull() {
    return currentSize == MAX_SIZE;
}

// Empty array?
static int isEmpty() {
    return currentSize == 0;
}

// Add element to buffer
void push_element(char x) {
    if (isFull()) {
        printf("Error: BUFFER IS FULL\n");
        return;
    }
    buffer[tail] = x;
    tail = (tail + 1) % MAX_SIZE;
    currentSize++;
    printf("Buffer updated with %c\n", x); 
}

// Take out element from buffer
char pop_element() {
    if (isEmpty()) {
        printf("Error: BUFFER IS EMPTY\n");
        return '\0'; // null in case of error
    }
    char value = buffer[head];
    head = (head + 1) % MAX_SIZE;
    currentSize--;
    return value;
}
