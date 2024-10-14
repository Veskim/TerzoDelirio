/*
 * WS2812B.h
 *
 *  Created on: May 28, 2024
 *      Author: Matteo Besutti
 */

#ifndef SRC_WS2812B_H_
#define SRC_WS2812B_H_

#include "math.h"
#include "main.h"    ///< Main project file
#include <stdlib.h>  ///< Standard library
#include <stdint.h>  ///< Std types

/*-------------IMPOSTAZIONI-------------*/
#define MAX_LED 9
#define USE_BRIGHTNESS 1
/*-------------IMPOSTAZIONI-------------*/

#define PI 3.14159265
#define TIM_HANDLE htim3
#define TIM_CH TIM_CHANNEL_3

extern TIM_HandleTypeDef(TIM_HANDLE); //serve per rendere disponibile alla libreria il gestore timer

void WS2812_Send(void);
void Set_Brightness(int brightness);
void Set_LED(int LEDNum, int Red, int Green, int Blue);

void Reset_LED(void);

void Attiva_LED(int num, int R, int G, int B);
#endif /* SRC_WS2812B_H_ */

