/**
  ******************************************************************************
  * @file    LwIP/LwIP_UDP_Echo_Client/Src/upd_demo.c
  * @author  MCD Application Team
  * @brief   UDP echo client
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "usart.h"
#include "lwip/netif.h"
#include "../../Product/h/ulog.h"
#include "lwip/api.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define UDP_DEMO_RX_BUFSIZE 100

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
osThreadId              UDPSendDemoHandle, UDPRecvDemoHandle;
static struct netconn   *udpconn;
static struct netbuf    *recvbuf;
static struct netbuf    *sentbuf;
uint8_t                 udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];
uint8_t                 udp_demo_sendbuf[] = "Wo cao ..................\r\n";

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Connect to UDP echo server
  * @param  None
  * @retval None
  */
void upd_demo_connect(void)
{
    err_t       err;
    ip_addr_t   destipaddr;
    ip_addr_t   srcipaddr;
    uint32_t    data_len = 0;
    struct pbuf *q;
    uint8_t     udp_demo_recvbuf[UDP_DEMO_RX_BUFSIZE];
    udpconn = netconn_new(NETCONN_UDP);                 //new net connect
    if(udpconn != NULL)                                 //check
    {
        IP4_ADDR(&srcipaddr, 192, 168, 0, 7);           //dest address
        err = netconn_bind(udpconn, &srcipaddr, 20012); //src address
        IP4_ADDR(&destipaddr, 192, 168, 0, 3);          //dest address
        netconn_connect(udpconn, &destipaddr, 20011);   //connect
        if(err == ERR_OK)   //connect is passed
        {
        }
        else
        {
            printf("UDP service is okay!!!\r\n");
        }
    }
    else
    {
        printf("UDP service is failure!!!r\n");
    }
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
void upd_demo_send(void)
{
}

/**
  * @brief This function is called when an UDP datagrm has been received on the port UDP_PORT.
  * @param arg user supplied argument (udp_pcb.recv_arg)
  * @param pcb the udp_pcb which received data
  * @param p the packet buffer that was received
  * @param addr the remote IP address from which the packet was received
  * @param port the remote port from which the packet was received
  * @retval None
  */
static void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    static uint32_t message_count;

    /*increment message count */
    message_count++;

    /* Free receive pbuf */
    pbuf_free(p);
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void appUDP_SendDemo(void const *argument)
{
    err_t       err;
    uint32_t    data_len = 0;
    struct pbuf *q;
    upd_demo_connect();
    sentbuf = netbuf_new();
    if(sentbuf != NULL)
    {
        netbuf_alloc(sentbuf, strlen((char *) udp_demo_sendbuf));
        sentbuf->p->payload = (char *) udp_demo_sendbuf;
        sentbuf->p->len = strlen((char *) udp_demo_sendbuf);
        if(UDPRecvDemoHandle != NULL)
        {
            vTaskResume(UDPRecvDemoHandle);     //Start Receive task
        }
    }

    while(1)
    {
        err = netconn_send(udpconn, sentbuf);   //Send the buffer
        if(err != ERR_OK)
        {
            printf("Sending Error:%d\r\n,", err);
            if(sentbuf != NULL)
            {
                netbuf_delete(sentbuf);         //Clear send buffer
            }
        }

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
void appUDP_RecvDemo(void const *argument)
{
    err_t       err;
    uint32_t    data_len = 0;
    struct pbuf *q;
    vTaskSuspend(NULL);
    while(1)
    {
        netconn_recv(udpconn, &recvbuf);
        if(recvbuf != NULL)
        {
            printf("receive data:\r\n");
            memset(udp_demo_recvbuf, 0, UDP_DEMO_RX_BUFSIZE);
            for(q = recvbuf->p; q != NULL; q = q->next)
            {
                if(q->len > (UDP_DEMO_RX_BUFSIZE - data_len))
                {
                    memcpy(udp_demo_recvbuf + data_len, q->payload, (UDP_DEMO_RX_BUFSIZE - data_len));  //????
                }
                else
                {
                    memcpy(udp_demo_recvbuf + data_len, q->payload, q->len);
                }

                data_len += q->len;
                if(data_len > UDP_DEMO_RX_BUFSIZE)
                {
                    break;
                }
            }

            data_len = 0;
            printf("%s\r\n", udp_demo_recvbuf);
            netbuf_delete(recvbuf);
        }
        else
        {
            osDelay(10);
        }
    }
}

/**
* @brief  FunctionName:   
*         @note: Please replace this comments!!!
* @param  input:  void
* @param  output: void
* @retval return value
*/
void UDP_DemoInit(void)
{
    /* definition and creation of SendMessageTask */
    osThreadDef(appUDP_RecvDemo, appUDP_RecvDemo, osPriorityAboveNormal, 0, 1000);
    UDPRecvDemoHandle = osThreadCreate(osThread(appUDP_RecvDemo), NULL);
    if(UDPRecvDemoHandle == NULL)
    {
        ;
    }

    /* definition and creation of SendMessageTask */
    osThreadDef(appUDP_SendDemo, appUDP_SendDemo, osPriorityAboveNormal, 0, 1000);
    UDPSendDemoHandle = osThreadCreate(osThread(appUDP_SendDemo), NULL);
    if(UDPSendDemoHandle == NULL)
    {
        ;
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
