#include <iostream>
#include "circular_array.hpp"

int main() {
    // Inserisce alcuni caratteri nell'array circolare
    push_element('A');
    push_element('B');
    push_element('C');
    push_element('D');
    push_element('E');

    // Questo inserimento dovrebbe fallire perché l'array è pieno
    push_element('F');

    // Rimuove e stampa alcuni elementi
    std::cout << "Pop: " << pop_element() << std::endl;
    std::cout << "Pop: " << pop_element() << std::endl;

    // Inserisce nuovi elementi dopo aver liberato dello spazio
    push_element('F');
    push_element('G');

    // Rimuove e stampa gli elementi rimanenti
    while (!isEmpty()) {
        std::cout << "Pop: " << pop_element() << std::endl;
    }

    return 0;
}
