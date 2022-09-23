/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BckLght_Pin GPIO_PIN_13
#define LCD_BckLght_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOH
#define KEY2_Pin GPIO_PIN_9
#define KEY2_GPIO_Port GPIOH
#define KEY3_Pin GPIO_PIN_10
#define KEY3_GPIO_Port GPIOH
#define KEY4_Pin GPIO_PIN_11
#define KEY4_GPIO_Port GPIOH
#define KEY5_Pin GPIO_PIN_12
#define KEY5_GPIO_Port GPIOB
#define KEY6_Pin GPIO_PIN_13
#define KEY6_GPIO_Port GPIOB
#define KEY7_Pin GPIO_PIN_14
#define KEY7_GPIO_Port GPIOB
#define KEY8_Pin GPIO_PIN_15
#define KEY8_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_5
#define BEEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
