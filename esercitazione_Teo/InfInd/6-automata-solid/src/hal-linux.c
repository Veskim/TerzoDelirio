#include "hal.h"
#include "fsm.h"
#include <stdio.h>

void debug(char* s)
{
    printf("%s", s);
}

void info(const char* s)
{
    printf("%s", s);
}

void error(const char* s)
{
    printf("%s", s);
}

void led_on(LED l)
{
    printf("TURNING ON LED %s\n", l == BLUE ? "BLUE" :
                                ( l == YELLOW ? "YELLOW" :
                                ( l == RED ? "RED" :
                                ( l == GREEN ? "GREEN" : "UNKNOWN COLOR"))));
}

void led_off(LED l)
{
    
    printf("TURNING OFF LED %s\n", l == BLUE ? "BLUE" :
                                ( l == YELLOW ? "YELLOW" :
                                ( l == RED ? "RED" :
                                ( l == GREEN ? "GREEN" : "UNKNOWN COLOR"))));
}