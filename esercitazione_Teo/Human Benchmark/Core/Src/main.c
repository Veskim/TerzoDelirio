/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "WS2812B.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/*
Definzione struttura coppie LED-Pulsante ed inizializzazione
- GPIO_Pin -> Il pin a livello scheda
- LED_Num -> Il numero del LED corrispondente
*/
typedef struct{
    uint16_t GPIO_Pulsante;
    int Led_num;
} Puls_Led;

Puls_Led Pulsanti[9];

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef enum {start = 0, running = 1, ended = 2} StateEnum;
#define MAX_LED 9 // Definizione della costante per il numero massimo di LED/Pulsanti
#define GREEN_BUTTON_PIN 4 // Aggiungi la definizione per il pulsante verde
#define TEMPI_QTY 11
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim16;
DMA_HandleTypeDef hdma_tim3_ch3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t s[200] = {'\0'};
int it_tot; //Pulsanti che verranno premuti durante la sessione
int it_cor; //Iterazione corrente
//int Colpiti;
//int Mancati;
double Tempi[TEMPI_QTY] = {0.0};
int puls_id = 0;
double veloce = 10000.0; // Inizializza a un valore alto per trovare il minimo
double lento = 0.0;
int pressed = 0;

StateEnum curr_state = start; //stato del processo, usato per dividere gli stati del programma
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM16_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
//static void TIM_GetCounter(TIM_TypeDef* TIM);
static void TIM_ResetCounter(TIM_TypeDef* TIM);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  //FARE DOUBLE CHECK CHE I COLLEGAMENTI HARDWARE RISPECCHIANO LE COPPIE SOFTWARE
  Pulsanti[0].GPIO_Pulsante = GPIO_PIN_0; //Pulsante 1 - PC0
  Pulsanti[0].Led_num = 0;

  Pulsanti[1].GPIO_Pulsante = GPIO_PIN_1 ; //Pulsante 2 - PC1
  Pulsanti[1].Led_num = 1;

  Pulsanti[2].GPIO_Pulsante = GPIO_PIN_2; //Pulsante 3 - PC2
  Pulsanti[2].Led_num = 2;

  Pulsanti[3].GPIO_Pulsante = GPIO_PIN_3; //Pulsante 4 - PC3
  Pulsanti[3].Led_num = 3;

  Pulsanti[4].GPIO_Pulsante = GPIO_PIN_4; //Pulsante 5 - PC4  //PULSANTE CENTRALE
  Pulsanti[4].Led_num = 4;

  Pulsanti[5].GPIO_Pulsante = GPIO_PIN_5; //Pulsante 6 - PC5
  Pulsanti[5].Led_num = 5;

  Pulsanti[6].GPIO_Pulsante = GPIO_PIN_6; //Pulsante 7 - PA6
  Pulsanti[6].Led_num = 6;

  Pulsanti[7].GPIO_Pulsante = GPIO_PIN_7; //Pulsante 8 - PA7
  Pulsanti[7].Led_num = 7;

  Pulsanti[8].GPIO_Pulsante = GPIO_PIN_8; //Pulsante 9 - PB8
  Pulsanti[8].Led_num = 8;


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM16_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  sprintf((char*)s,"Inizializzazione e Caricamento dati...\r\n\r\n");
  HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
  memset(s ,0, sizeof(s));
  HAL_Delay(100);
  Reset_LED();
  HAL_TIM_Base_Stop(&htim16);
  TIM_ResetCounter(TIM16);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while(1){
      switch(curr_state){
      case start:
        //setup o reset dati
    	it_tot = TEMPI_QTY;
        it_cor = 0;
        //Colpiti = 0;
        //Mancati = 0;
        lento = 0.0;
        veloce = 1000.0;
        for(int i = 0; i < it_tot; i++) Tempi[i] = 0;

        sprintf((char*)s,"Iterazioni Totali: %d \r\nTempo massimo di reazione: 2 secondi\r\n", it_tot);
        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
        memset(s ,0, sizeof(s));
        sprintf((char*)s,"Premere il Pulsante Verde per Iniziare.\r\n");
        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
        memset(s,0,sizeof(s));
        Attiva_LED(GREEN_BUTTON_PIN, 0, 255, 0);
        while(curr_state == start){ //dovrebbe bloccarsi qua
        	HAL_Delay(250);
        }
        break;

      case running:
    	HAL_TIM_Base_Stop(&htim16);
		TIM_ResetCounter(TIM16);
		sprintf((char*)s,"\r\nINIZO SESSIONE in 3 secondi\r\nIl primo è di assestamento, non verrà contato.\r\n");
		HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
		memset(s,0,sizeof(s));
        Attiva_LED(4, 0,0,0);
        HAL_Delay(3000);
        pressed = 0;

        while(it_cor < it_tot){
//            sprintf((char*)s,"Tentativo: %d \r\n", it_cor);
//            HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
//			memset(s,0,sizeof(s));
            //wait = rand()%2000 +1000;
            puls_id = rand()%MAX_LED;
            Attiva_LED(puls_id, 0, 50, 140);
//            sprintf((char*)s,"Pulsante attivo: %d \r\n", puls_id);
//			HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
//			memset(s,0,sizeof(s));

            TIM_ResetCounter(TIM16); // Reset del contatore del timer
            HAL_TIM_Base_Start_IT(&htim16); //&htim16



            HAL_Delay(2000);
            // Questa parte dovrebbe essere implementata per aspettare l'input dell'utente
            // Attualmente il codice non aspetta e continua direttamente

            // Logica per terminare il test o andare al successivo tentativo
            // Temporaneamente sostituito dall'interrupt del timer, ha una priorità maggiore quindi sarà sopra agli EXTI
//            if(__HAL_TIM_GET_COUNTER(&htim16) > 2000){
//                Mancati++;
//                sprintf((char*)s, "Troppo lento!\r\n");
//                HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
//				memset(s,0,sizeof(s));
//                HAL_TIM_Base_Stop(&htim16); // Assicurati di fermare il timer
//            }
//            HAL_UART_Transmit(&huart1, s, strlen((char*)s), 100);
//            memset(s, 0, sizeof(s));
        }

        //fine sessione, cambia stato
        curr_state = ended;
        break;

      case ended:
        //Calcoli finali, fuori dal while dato che la sessione è finita.
    	//EVITA IL PRIMO GIRO DATO CHE IL TIMER DA PROBLEMI
        double media = 0;
        for(int i = 0; i < it_tot; i++){
        	if(Tempi[i] != -1.0)
        		media += Tempi[i];
        }
        media = media / it_tot-1;

        for(int i = 1; i < it_tot; i++){
        	if(Tempi[i] > lento && Tempi[i]!=-1.0) lento = Tempi[i];
        	else if(Tempi[i] <= veloce && Tempi[i]!=-1.0) veloce = Tempi[i];
        }


        ///////----RESOCONTO----///////
        sprintf((char*)s,"Test completato, ecco i risultati:\r\n");
        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
		memset(s,0,sizeof(s));
        for(int i = 1; i < it_tot; i++){
            sprintf((char*)s,"Tentativo %d:\tTempo: %.2lf ms\r\n", i, Tempi[i]);
            HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
			memset(s,0,sizeof(s));
        }
//        sprintf((char*)s,"\r\nNumero Pulsanti Totali:%d\tPulsanti Corretti:%d \tPulsanti Mancati:%d \r\nTempo Medio: %.2lf ms\tReazione Piu\' Veloce: %.2lf ms\tReazione piu\' Lenta: %.2lf ms\r\n",it_tot, Colpiti, Mancati, media, veloce, lento);
//        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
//        memset(s ,0, sizeof(s));
        sprintf((char*)s,"\r\nNumero Pulsanti Totali:%d\r\nTempo Medio: %.2lf ms\tReazione Piu\' Veloce: %.2lf ms\tReazione piu\' Lenta: %.2lf ms\r\n", (it_tot-1), media, veloce, lento);
        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
        memset(s ,0, sizeof(s));
        sprintf((char*)s, "Premere il pulsante verde per ricominciare.\r\n");
        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
        memset(s ,0, sizeof(s));
        Attiva_LED(GREEN_BUTTON_PIN, 0, 255, 0);
        while(curr_state == ended){ //dovrebbe bloccarsi qua
        	HAL_Delay(250);
		}
		Reset_LED();
        break;
      }
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 72-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 2231;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 64515;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if(curr_state == running){
    //int pulsanteCorretto = 0;
	HAL_TIM_Base_Stop(&htim16);
    Attiva_LED(puls_id, 0,0,0);
    for(int i = 0; i < MAX_LED; i++){
      if(puls_id == Pulsanti[i].Led_num){
        //pulsanteCorretto = 1; // Imposta il flag per indicare che il pulsante corretto è stato premuto
        Tempi[it_cor] = __HAL_TIM_GET_COUNTER(&htim16) / 100.0; // esempio: calcolo del tempo in secondi
        //Colpiti++;
//        sprintf((char*)s,"Premuto il pin %d\r\n", GPIO_Pin);
//		HAL_UART_Transmit(&huart1, s, sizeof(s), 1000);
//		memset(s,0,sizeof(s));
        it_cor++;
        // TIM_ResetCounter(TIM16); // Reset del contatore del timer
        return;
      }
    }

    // Pulsante sbagliato, gestione del caso
//     if (!pulsanteCorretto) {
//        sprintf((char*)s, "Pulsante sbagliato!\r\n");
//        HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
//		memset(s,0,sizeof(s));
//		it_cor++;
//        Mancati++;
//        return;
//     }
  }
  else if(curr_state == start && GPIO_Pin == GPIO_PIN_4){ // Assicurati che il pin sia corretto
    curr_state = running; // Cambia stato a running per iniziare il test
  }
  else if(curr_state == ended && GPIO_Pin == GPIO_PIN_4){
    curr_state = start; // Ritorna allo stato iniziale per ricominciare
  }
}

static void TIM_ResetCounter(TIM_TypeDef* TIM) {
  __HAL_TIM_SET_COUNTER(&htim16, 0);
}

/**
 * Rifacimento della funzione HAL_Delay, ci aggiungiamo una flag per impedire il funzionamento dei pulsanti
 * POSSIAMO CHIAMARE INTERRUPT DURANTE UN DELAY
 */
void HAL_Delay(uint32_t Delay)
{
  //pauseFlag = 1;
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;


  /* Add a period to guaranty minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)uwTickFreq;
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }

  //pauseFlag=0;
}

// La funzione viene chiamata se il timer scade
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	HAL_TIM_Base_Stop(&htim16);
	//Mancati++;
	Tempi[it_cor] = -1.0;
	sprintf((char*)s, "Tempo Scaduto!\r\n");
	HAL_UART_Transmit(&huart1, s, sizeof(s), 100);
	memset(s,0,sizeof(s));
	it_cor++;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
