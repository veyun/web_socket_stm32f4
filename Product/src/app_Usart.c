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
#include "lwip/netif.h"
#include "../../Product/h/ulog.h"

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

/**Buffer length*/
#define SEND_BUFF_LENGTH    100

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/

/** @addtogroup app_smart_uart_macro
  * @{  */
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, HAL_TICK_FREQ_100HZ);

    //HAL_UART_Transmit_DMA
    return(ch);
}

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup RCC_Private_Variables RCC Private Variables
  * @{
  */
osThreadId      UsartSendTaskHandle;
static uint8_t  ETHStatus = 0xff, ETHAddress = 0xff;
uint32_t        ETHEntryInterruption = 0;
uint8_t         StringBuff[SEND_BUFF_LENGTH] = { 0 };

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
extern uint8_t  IP_ADDRESS[];
extern uint8_t  NETMASK_ADDRESS[];
extern uint8_t  GATEWAY_ADDRESS[];

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
void my_console_logger(ulog_level_t level, char *msg)
{
    printf("[%s][%d]%s\n", ulog_level_name(level), osKernelSysTick(), msg);
}

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
    ULOG_INIT();
    ULOG_SUBSCRIBE(my_console_logger, ULOG_WARNING_LEVEL);

    //printf("page 1     ");
    for(;;)
    {
        CntSendTask = osKernelSysTick();

        //memset(StringBuff, 0, SEND_BUFF_LENGTH);
        //sprintf((char *) &StringBuff[0], "Running time:%d,Address:%d", CntSendTask, ETHAddress);
        //ULOG_WARNING("EntryInt:%d------\n", ETHEntryInterruption);

        //printf("t3.txt=\"192.168.88.%d\"%s", (uint8_t) CntSendTask, EndSendChar);
        //SEGGER_RTT_printf(0,"t3.txt=\"192.168.88.%d\"%s\r\n", (uint8_t) CntSendTask, "RTT");
        osDelay(1000);
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
    osThreadDef(UsartSendTask, appUsart_SendTask, osPriorityAboveNormal, 0, 300);
    UsartSendTaskHandle = osThreadCreate(osThread(UsartSendTask), NULL);
    if(UsartSendTaskHandle == NULL)
    {
        ;
    }
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
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUsart_SetETHStatus(uint8_t status, uint8_t address)
{
    osThreadSuspendAll();
    ETHStatus = status;
    ETHAddress = address;
    osThreadResumeAll();
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUsart_IncreaseData(void)
{
    ETHEntryInterruption++;
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void ethernetif_notify_conn_changed(struct netif *netif)
{
    ip_addr_t   ipaddr;
    ip_addr_t   netmask;
    ip_addr_t   gw;
    if(netif_is_link_up(netif))
    {
        IP_ADDR4(&ipaddr, IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
        IP_ADDR4(&netmask, NETMASK_ADDRESS[0], NETMASK_ADDRESS[1], NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
        IP_ADDR4(&gw, GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1], GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);
        netif_set_addr(netif, &ipaddr, &netmask, &gw);

        /* When the netif is fully configured this function must be called.*/

        //netif_set_up(netif);
    }
    else
    {
        /*  When the netif link is down this function must be called.*/

        //netif_set_down(netif);
    }

    ULOG_WARNING("========>Enthernet status is:!!%x<========\r\n", netif->flags);
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void HAL_Delay(uint32_t Delay)
{
    osDelay(Delay);
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
