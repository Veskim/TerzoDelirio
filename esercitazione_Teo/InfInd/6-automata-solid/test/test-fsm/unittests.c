/*
 * These are the Unit Tests for FSM module. Unit tests are tests where we do not test
 * the module in conjunction with other modules, but only its standalone functionalities.
 * In our case, the sfn() function is standalone, unkile the mfn() function, which depends on HAL module.
 * 
 * Typically, test follow a so-called "Arrange, Act, Assert" scheme, as follows
 * - Arrange: set up every data structure, and expected test result
 * - Act: invoke functionality
 * - Assert: check that returned value matches the expected one. This is done with the help
 *           of one (or more) functions called "assert", which do the work for us.
 *           They are typically implemented in the SDK, and for the sake of teching I implemented
 *           my (very stupid) "myassert" function, here. "Real" ASSERTs funcs are a bit more
 *           complex, but their behavior is similar to mine.
 * 
 * Good programmers write the name of test functions in a known (snakecase) pattern:
 *       <MODULE NAME> _ <INPUT GIVEN> _< EXPECTED_OUTPUT>
 * Ex (here below):
 *       sfm           _ wrongstate    _ returnerrorcode
 */


#include "fsm.h"

#include "assert.h"

/*
 * Test that if we give a wrong state, then sfm returns '-3', no matter which char we pass to it
 */
void sfn_wrongstate_returnerrorcode()
{
    // Arrange
    int s = 4;
    char c = '?';
    int expectedval = -3;
    
    // Act
    int ret = sfn(s, c);

    // Assert
    myassert(ret == expectedval, "sfn_wrongstate_returnerrorcode");
}

/*
 * Test that if we give a correct state, but a wrong input, then sfm returns '-1'
 */
void sfn_goodstateandwronginput_returnerrorcode()
{
    // Arrange
    int s = 0;
    char c = '?';
    // NOTE this test is badly written on purpose, and will fail, because
    // I expect -5, while the correct value is -1, to give an example of failed test
    //int expectedval = -1;
    int expectedval = -5;
    
    // Act
    int ret = sfn(s, c);

    // Assert
    myassert(ret == expectedval, "sfn_goodstateandwronginput_returnerrorcode");
}

int main()
{
    // Run tests, one after another
    sfn_wrongstate_returnerrorcode();
    sfn_goodstateandwronginput_returnerrorcode();
}