#include <iostream>
#include "sfm.hpp"

using namespace std;

const char inputs[] = {'a', 'a', 'b', 'c'};
int ninputs = sizeof(inputs) / sizeof(inputs[0]);

/*
 * Gets next inputs, or 'x' if no inputs available.
 * WARNING: this function shifts the input, once you call it!
 */
char next()
{
	static int i = 0;
	if(i >= ninputs)
		return 'x';
	return inputs[i++];
}

/*
 * Computes next state. Returns the following
 *   >=0 : the next state
 *   -1  : input sequence not legal
 *   -2  : we're in final state
 *   -3  : internal error
 */

bool isFinalState(int s)
{
	return s == 3;
}

int main()
{
	cout << "Inputs size is " << ninputs << endl;
	int currState = 0;
	int state = -1;
	char c;
	
	while(1)
	{
		// Get next input
		c = next();
		
		// We ran out of inputs, and
		if(c == 'x')
		{
			if(!isFinalState(currState))
				goto error;
			// This should never happen, if our algo works well
			else
				break;
		}
		
		cout << "Next input word is " << c << endl; //", current state is " << currState << endl;
		
		state = sfn(currState, c);
		
		//cout << "Next state will be " << state << endl;

		mfn(state);
		
		// Check for errors
		if(state < 0)
			goto error;

		if(isFinalState(state))
			break;
		
		// Update curr state
		currState = state;
	}
	
	cout << "Input sequence is legal for our Language" << endl;
	return 0;

error:
	cout << "ERROR!" << endl;
	cout << "Input " << c << " not legal for state " << currState << endl;
	cout << "Error code is " << state << endl;
	return state;
}
