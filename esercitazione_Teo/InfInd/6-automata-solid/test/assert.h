/* This file is typically defined by any dev SDK.
 * Here I re-define it for educational purposes. */
#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * If condition is not true, we print an error message and die.
 */
static inline void myassert(bool condition, const char *msg)
{
    if(!condition)
    {
        printf("[");
        printf(msg);
        printf("] - Assert failed!\n");
        exit(0);
    }
}

#endif