#include <iostream>
#include "circular_array.hpp"

int main() {
    // push element
    push_element('A');
    push_element('B');
    push_element('C');
    push_element('D');
    push_element('E');

    // should fail
    push_element('F');

    // pop and print some elements
    std::cout << "Pop: " << pop_element() << std::endl;
    std::cout << "Pop: " << pop_element() << std::endl;

    // new insert
    push_element('F');
    push_element('G');

    // pop and print all element
    while (!isEmpty()) {
        std::cout << "Pop: " << pop_element() << std::endl;
    }

    return 0;
}
