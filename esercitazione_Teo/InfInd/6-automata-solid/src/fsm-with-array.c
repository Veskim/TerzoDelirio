#include "hal.h"

// Here, stored as array
// TODO is it really responsibility of the FSM module knowing how input is fetched? Should we inject this?
const char inputs[] = {'a', 'a', 'b', 'c'};
int ninputs = sizeof(inputs) / sizeof(inputs[0]);

char next()
{
	static int i = 0;
	if(i >= ninputs)
		return 'x';
	return inputs[i++];
}

int sfn(int currState, char input)
{
	switch(currState)
	{
		case 0:
			switch(input)
			{
				case 'a': return 2;
				case 'b': return 1;
				case 'c': return 3;
				default:  break;
			}
			break;
			
		case 1:
			switch(input)
			{
				case 'a': break;
				case 'b': return 1;
				case 'c': return 3;
				default:  break;
			}
			break;
			
		case 2:
			switch(input)
			{
				case 'a': return 0;
				case 'b': break;
				case 'c': break;
				default: break;
			}
			break;
			
		case 3:
			return -2;
			
		default:
			return -3;
	}
	
	// If we're here, it's an error
	return -1;
}

void mfn(int currState)
{
	switch(currState)
	{
		case 0:
			led_on(BLUE);
			break;
			
		case 1:
			led_on(YELLOW);
			break;
			
		case 2:
			led_on(YELLOW);
			break;
			
		case 3:
			led_on(GREEN);
			break;
			
		default:
			led_on(RED);
			break;
	}
}

int isFinalState(int s)
{
	return s == 3;
}