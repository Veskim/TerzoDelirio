#include <iostream>
#include "circular_array.hpp"

// Definizione della dimensione massima del buffer
#define MAX_SIZE 5

// Variabili statiche
char buffer[MAX_SIZE]; // Buffer circolare
int head = 0;          // Indice della testa
int tail = 0;          // Indice della coda
int currentSize = 0;   // Numero di elementi attuali

// Funzione per verificare se il buffer è pieno
bool isFull() {
    return currentSize == MAX_SIZE;
}

// Funzione per verificare se il buffer è vuoto
bool isEmpty() {
    return currentSize == 0;
}

// Funzione per inserire un elemento nel buffer circolare
void push_element(char x) {
    if (isFull()) {
        std::cout << "Error: BUFFER IS FULL\n";
        return;
    }
    buffer[tail] = x;
    tail = (tail + 1) % MAX_SIZE; // Cicla l'indice della coda
    currentSize++;
    std::cout << "Buffer updated with " << x << "\n";
}

// Funzione per rimuovere un elemento dal buffer circolare
char pop_element() {
    if (isEmpty()) {
        std::cout << "Error: BUFFER IS FULL\n";
        return '\0'; // Restituisce il carattere nullo in caso di errore
    }
    char value = buffer[head];
    head = (head + 1) % MAX_SIZE; // Cicla l'indice della testa
    currentSize--;
    return value;
}
