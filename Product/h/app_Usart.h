/**
  ******************************************************************************
  * @file    stm32f4xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_USART_H
#define APP_USART_H
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
/* Include RCC HAL Extended module */

/* (include on top of file since RCC structures are defined in extended file) */

/** @addtogroup app_smart
  * @{
  */

/** @defgroup app_smart_uart
  * @brief handle the uart event
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */
extern void appUsart_SetETHStatus(uint8_t status, uint8_t address);
extern void appUsart_OutputNetStatus(uint8_t status);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif /* APP_USART_H */
