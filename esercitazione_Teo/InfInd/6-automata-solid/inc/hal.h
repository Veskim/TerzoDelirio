/*
 * This header is the protocol to Hardware Abstraction Layer pattern.
 * Every platform should implement these basic functionalities
 */

#ifndef __HAL_H__
#define __HAL_H__

/*
 * Basic DEBUG-level printing.
 * NOTE, here we only provide a printing of a simple string
 */
void debug(char* s);

/*
 * INFO-level printings.
 */
void info(const char* s);

/*
 * ERROR-level printing.
 */
void error(const char* s);

typedef enum LED
{
    BLUE = 0,
    RED,
    YELLOW,
    GREEN
} LED;

/*
 * Turns a single led ON
*/
void led_on(LED l);

/*
 * Turns a single led OFF
*/
void led_off(LED l);

#endif
