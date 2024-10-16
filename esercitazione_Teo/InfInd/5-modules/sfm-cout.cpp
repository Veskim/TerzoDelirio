#include <iostream>
#include "sfm.hpp"
using namespace std;

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
/*
 * Computes output. Moore machine.
 */
void mfn(int currState)
{
	// debug
	cout << "current state is S" << currState << endl;
	switch(currState)
	{
		case 0:
			//turn on (blue)
			cout << "BLUE LED ON" << endl;
			break;
			
		case 1:
			cout << "YELLOW LED ON" << endl;
			break;
			
		case 2:
			cout << "YELLOW LED ON" << endl;
			break;
			
		case 3:
			cout << "GREEN LED ON" << endl;
			break;
			
		default:
			cout << "RED LED ON" << endl;
			break;
	}
}