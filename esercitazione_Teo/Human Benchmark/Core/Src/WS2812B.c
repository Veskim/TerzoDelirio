/*
 * WS2812B.c
 *
 *  Created on: May 28, 2024
 *      Author: Matteo Besutti
 */

#include "WS2812B.h"

int datasentflag;
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4]; //For Brightness
uint16_t pwmData[(24*MAX_LED)+50];

/**
  * @brief Loads LED data into the DMA and pushes them into the LED
  * @param None
  * @retval None
  */
void WS2812_Send (void){
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 of 90
			}

			else pwmData[indx] = 30;  // 1/3 of 90

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&TIM_HANDLE, TIM_CH, (uint32_t *)pwmData, indx);
	while (!datasentflag){};
	datasentflag = 0;
}

/**
  * @brief Set LED Colours
  * @param int LEDNum
  * @param int Red
  * @param int Green
  * @param int Blue
  * @retval None
  */
void Set_LED (int LEDNum, int Red, int Green, int Blue)
{
	LED_Data[LEDNum][0] = LEDNum;
	LED_Data[LEDNum][1] = Green;
	LED_Data[LEDNum][2] = Red;
	LED_Data[LEDNum][3] = Blue;
}

/**
  * @brief Set LED Brightness, goes from 0 to 45
  * @param int
  * @retval None
  */
void Set_Brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&TIM_HANDLE, TIM_CH);
	datasentflag=1;
}

/**
 * @brief Inizializzazione dei led, serve per controllare che funzionino
 */
void LED_Test(){
	int R = 0;
	int G = 0;
	int B = 0;
	for(int Led_Num=0; Led_Num<MAX_LED; Led_Num++){
		for (int i=MAX_LED; i>0; i--){
			if(Led_Num==i){
				LED_Data[Led_Num][0]=Led_Num;
				LED_Data[Led_Num][1]=G;
				LED_Data[Led_Num][2]=R;
				LED_Data[Led_Num][3]=B;
			}
			else{
				LED_Data[Led_Num][0]=Led_Num;
				LED_Data[Led_Num][1]=0;
				LED_Data[Led_Num][2]=0;
				LED_Data[Led_Num][3]=0;
			}
			Set_Brightness(40);
			WS2812_Send();
			HAL_Delay(50);
		}
		G += 25;
		R += 25;
		B += 25;
	}
}


/**
  * @brief Set LED Colours
  * @param int LEDNum
  * @param int Red
  * @param int Green
  * @param int Blue
  * @retval None
  */
void Reset_LED (void)
{

	for(int Led_Num=0; Led_Num<MAX_LED; Led_Num++){
		Set_LED(Led_Num, 0, 0, 0);
	}
	WS2812_Send();

}


/**
 * @brief Funzione di attivazione di un singolo LED, richiedendo il numero del led e quale colorazione assegnarli.
 * Richiede l'uso di altre funzioni della libreria ed una funzione nuova che resetti tutta la stricia (reset -> tutti i led hanno valore 0)
 */
void Attiva_LED(int num, int R, int G, int B){
	Reset_LED();
	Set_LED(num, R, G, B);
	Set_Brightness(40);
	WS2812_Send();
}













