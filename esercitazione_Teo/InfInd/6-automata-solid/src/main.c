#include "fsm.h"
#include "hal.h"

int main()
{
	int currState = 0;
	int state = -1;
	char c;
	
	while(1)
	{
		// Get next input
		c = next();
		
		// We ran out of inputs, and
		if(c == INPUT_END)
		{
			if(!isFinalState(currState))
				goto error;
			// This should never happen, if our algo works well
			else
				break;
		}
		
		// DEBUG with char aren't implemented yet, nor with int params
		// debug("Next input word is ");
		// debug(c);
		// debug("\n");
		
		state = sfn(currState, c);
		
		// debug("Next state will be ");
		// debug(state);
		// debug("\n");

		mfn(state);
		
		// Check for errors
		if(state < 0)
			goto error;

		if(isFinalState(state))
			break;
		
		// Update curr state
		currState = state;
	}
	
	debug("Input sequence is legal for our Language\n");
	return 0;

error:
	error("ERROR!\n");
	error("Input not legal\n");
	error("Error code is :");
	//error(state);
	return state;
}
