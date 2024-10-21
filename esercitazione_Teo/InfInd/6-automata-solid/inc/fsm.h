/*
 * This is contract for basic Finite State Machine automata.
 */
#ifndef __FSM_H__
#define __FSM_H__

/*
 * This character defines the end of our input.
 * TODO we could also make it implementation-specific, i.e., the .c file shall specify it,
 * and we retrieve it with a function, or a global var.
 */
#define INPUT_END 'x'

/*
 * State function. Returns the following
 *   >=0 : the next state
 *   -1  : input sequence not legal
 *   -2  : we're in final state
 *   -3  : internal error
 */
int sfn(int currState, char input);

/*
 * Machine function. Moore machine.
 */
void mfn(int currState);

/*
 * Returns true if state given as input is the final state
 */
int isFinalState(int s);

/*
 * Gets next inputs, or 'x' if no inputs available.
 * WARNING: this function shifts the input, once you call it!
 */
char next();

#endif