#include <stdio.h>
#include "circular_array.h"

int main() {
    // push element
    push_element('A');
    push_element('B');
    push_element('C');
    push_element('D');
    push_element('E');

    // should fail since the array is full
    push_element('F');

    // test pop element and print
    printf("Pop: %c\n", pop_element());
    printf("Pop: %c\n", pop_element());

    // Add new element
    push_element('F');
    push_element('G');

    // print all
    while (pop_element() != '\0'); // Pop untill you get error
    
    return 0;
}
