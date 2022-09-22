/**
  ******************************************************************************
  * @file    app_usart.c
  * @author  M.W
  * @brief   Send the message via USART1.
  *          This file provides firmware functions to manage the following
  *          functionalities of the send the message:
  *           + usart
  *           + printf
  *
  @verbatim
  ==============================================================================
                      ##### Handle Usart #####
  ==============================================================================
    [..]
*/

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "stdio.h"
#include "usart.h"
#include "../../SEGGER_RTT_V780a/RTT/SEGGER_RTT.h"

/** @addtogroup app_smart
  * @{
  */

/** @defgroup app_smart_uart
  * @brief handle the uart event
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/** @addtogroup app_smart_uart_typedef
  * @{  */

/**
  * @}
  */

/* Private define ------------------------------------------------------------*/

/** @addtogroup app_smart_uart_define
  * @{  */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE   int __io_putchar (int ch)
#else
#define PUTCHAR_PROTOTYPE   int fputc (int ch, FILE *f)
#endif

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @addtogroup app_smart_uart_macro
  * @{  */
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, HAL_TICK_FREQ_100HZ);
    return(ch);
}

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup RCC_Private_Variables RCC Private Variables
  * @{
  */
osThreadId  UsartSendTaskHandle;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  *  @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal/external oscillators
      (HSE, HSI, LSE, LSI, PLL, CSS and MCO) and the System busses clocks (SYSCLK, AHB, APB1
       and APB2).

    [..] Internal/external clock and PLL configuration
        
@endverbatim
*/

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUsart_SendTask(void const *argument)
{
    /* Infinite loop */
    uint32_t    CntSendTask;
    char        EndSendChar[4] = { 0xff, 0xff, 0xff, 0x00 };
    printf("page 1     ");
    for(;;)
    {
        CntSendTask = osKernelSysTick();

        printf("t3.txt=\"RunningCount:%d\"%s", CntSendTask,EndSendChar);
        //printf("t3.txt=\"192.168.88.%d\"%s", (uint8_t) CntSendTask, EndSendChar);
			  //SEGGER_RTT_printf(0,"t3.txt=\"192.168.88.%d\"%s\r\n", (uint8_t) CntSendTask, "RTT");
        osDelay(100);
    }
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUsart_TaskInit(void)
{
    /* definition and creation of SendMessageTask */
    osThreadDef(UsartSendTask, appUsart_SendTask, osPriorityNormal, 0, 128);
    UsartSendTaskHandle = osThreadCreate(osThread(UsartSendTask), NULL);
}


/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUsart_OutputNetStatus(uint8_t status)
{
    switch(status)
    {
        case 0:     printf("Internet connection is lossing!!\r\n"); break;
        default:    printf("Internet connection is okay!!\r\n"); break;
    }
}

/**
  * @}
  */

/**
  * @}end the file group
  */

/**
  * @}//end the product
  */
