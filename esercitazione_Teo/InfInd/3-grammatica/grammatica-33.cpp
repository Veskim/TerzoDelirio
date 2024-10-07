#include <iostream>
#include <string>

using namespace std;

// Input della frase (sequenza di parole che vogliamo riconoscere)
const string inputs[] = {"il", "gatto", "mangia", "il", "topo"};
int ninputs = sizeof(inputs) / sizeof(inputs[0]);

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
 * Funzione che calcola il prossimo stato in base allo stato corrente e l'input.
 */
int nextState(int currState, const string &input) {
    switch (currState) {
        case INIZIO:
            if (input.compare("il") == 0) {
                return ARTICOLO_SOGGETTO;
            }
            break;

        case ARTICOLO_SOGGETTO:
            if (input.compare("gatto") == 0 || input.compare("topo") == 0 || input.compare("sasso") == 0) {
                return NOME_SOGGETTO;
            }
            break;

        case NOME_SOGGETTO:
            if (input.compare("mangia") == 0 || input.compare("beve") == 0) {
                return VERBO;
            }
            break;

        case VERBO:
            if (input.compare("il") == 0) {
                return ARTICOLO_OGGETTO;
            }
            break;

        case ARTICOLO_OGGETTO:
            if (input.compare("gatto") == 0 || input.compare("topo") == 0 || input.compare("sasso") == 0) {
                return NOME_OGGETTO;
            }
            break;

        case NOME_OGGETTO:
            return FINALE; // Stato finale raggiunto
    }
    return ERRORE; // Stato di errore se nessuna transizione è valida
}

/*
 * Verifica se lo stato corrente è lo stato finale
 */
bool isFinalState(int s) {
    return s == FINALE;
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

        cout << "Next input word is " << word << ", current state is " << currState << endl;

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
    cout << "Input \"" << word << "\" not legal for state " << currState << endl;
    cout << "Error code is " << state << endl;
    return state;
}