// Matteo Girelli ft. chat gpt, ingegneria informatica, mantova
#include <iostream>
#include <string>
#include <map>
using namespace std;

// Stati della macchina a stati
enum Stati {
    INIZIO = 0,
    ARTICOLO_SOGGETTO,
    NOME_SOGGETTO,
    VERBO,
    ARTICOLO_OGGETTO,
    NOME_OGGETTO,
    FINALE,
    ERRORE
};

// Input della frase (sequenza di parole che vogliamo riconoscere)
//const string inputs[] = {"il", "gatto", "mangia", "il", "topo"}; // stringa giusta
const string inputs[] = {"il", "sasso", "mangia", "il", "topo", "gatto"}; // stringa giusta
//const string inputs[] = {"il", "gatto", "mangia", "il", "topo", "mangia", "il", "sasso"}; // stringa lunga
//const string inputs[] = { "gatto", "mangia", "il", "topo"}; // stringa sbagliata
int ninputs = sizeof(inputs) / sizeof(inputs[0]);

// Mappatura delle parole a indici numerici per facilitare la ricerca nella tabella
map<string, int> inputMap = {
    {"il", 0},
    {"gatto", 1},
    {"topo", 2},
    {"sasso", 3},
    {"mangia", 4},
    {"beve", 5}
};

// Tabella di transizione degli stati
// Righe: stati correnti
// Colonne: input (parole) -> valori numerici (usati come indici nella tabella)
int stateTable[7][6] = { // Nota: le righe devono corrispondere al numero di stati (7)
    // il     gatto   topo    sasso   mangia  beve
    { ARTICOLO_SOGGETTO, ERRORE, ERRORE, ERRORE, ERRORE, ERRORE }, // INIZIO
    { ERRORE, NOME_SOGGETTO, NOME_SOGGETTO, NOME_SOGGETTO, ERRORE, ERRORE }, // ARTICOLO_SOGGETTO
    { ERRORE, ERRORE, ERRORE, ERRORE, VERBO, VERBO }, // NOME_SOGGETTO
    { ARTICOLO_OGGETTO, ERRORE, ERRORE, ERRORE, ERRORE, ERRORE }, // VERBO
    { ERRORE, NOME_OGGETTO, NOME_OGGETTO, NOME_OGGETTO, ERRORE, ERRORE }, // ARTICOLO_OGGETTO
	{ FINALE, FINALE, FINALE, FINALE, FINALE, FINALE }, // Stato finale (accetta qualsiasi input, quindi finale)
	{ ERRORE, ERRORE, ERRORE, ERRORE, ERRORE, ERRORE }, // NOME_OGGETTO
};

/*
 * Funzione per ottenere il prossimo input (parola).
 * Avanza l'indice alla parola successiva.
 */
string next() {
    static int i = 0;
    if (i >= ninputs)
        return "x"; // Segnala che abbiamo esaurito l'input
    return inputs[i++];
}

/*
 * Funzione che calcola il prossimo stato in base allo stato corrente e all'input.
 * Utilizza la tabella di transizione degli stati.
 */
int nextState(int currState, const string &input) {
    // Trova l'indice associato all'input (parola)
    if (inputMap.find(input) != inputMap.end()) {
        int inputIndex = inputMap[input];
        // Ritorna il prossimo stato dalla tabella
        return stateTable[currState][inputIndex];
    }
    return ERRORE; // Se l'input non è valido
}

/*
 * Verifica se lo stato corrente è lo stato finale
 */
bool isFinalState(int s) {
    return s == ninputs; // se lo stato è grande quanto la mia stringa sono alla fine
	//return s == FINALE; // ERROR: mi conta il valore di errore per uscire
}

int main() {
    cout << "Inputs size is " << ninputs << endl;
    int currState = INIZIO;
    int state = -1;
    string word;

    while (true) {
        // Prendi il prossimo input (parola)
        word = next();

        // Abbiamo esaurito gli input, controlla se siamo nello stato finale
        if (word == "x") {
            if (!isFinalState(currState))
                goto error;
            // La sequenza è legale se siamo nello stato finale
            else
                break;
        }

        cout << "Next input word is \"" << word << "\", current state is " << currState << endl;

        // Calcola il prossimo stato
        state = nextState(currState, word);

        // Controlla per errori
        if (state == ERRORE)
            goto error;

        cout << "Next state will be " << state << endl;

        // Se abbiamo raggiunto lo stato finale, esci dal ciclo
        if (isFinalState(state))
            break;

        // Aggiorna lo stato corrente
        currState = state;
    }

    cout << "Input sequence is legal for our Language" << endl;
    return 0;

error:
    cout << "ERROR!" << endl;
    cout << "Input \"" << word << "\" not legal for state S" << currState << endl;
    cout << "Error code is " << state << endl;
    return state;
}