/*
 * uart_debug.c
 *
 *  Created on: Mar 9, 2020
 *      Author: AngBluCat
 */

/* COED BEGIN UART_DEBUG */

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"


/* UART 发送缓冲 */
//#define UART_DEBUG_BUFF_SIZE  0
//static uint8_t UART_Debug_Buff[UART_DEBUG_BUFF_SIZE];
//static uint32_t UART_Debug_BuffIndex;

/* 重定向printf */
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE  int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE  int fputc(int ch, FILE *stream)
#endif

#if 0
//如果使用UART_Debug_Printf函数请使用以下代码
PUTCHAR_PROTOTYPE
{
  UART_Debug_Buff[UART_Debug_BuffIndex] = (uint8_t) ch;
  UART_Debug_BuffIndex ++;
  return ch;
}
#else

/* UART句柄，用于DEBUG输出，需要初始化映射，调用UART_Debug_Remap函数 */
UART_HandleTypeDef *UART_Debug_Handle = &huart2;

//如果使用printf函数请使用以下代码
PUTCHAR_PROTOTYPE
{
    //注意下面第一个参数是&husart1，因为cubemx配置了串口1自动生成的
    HAL_UART_Transmit(UART_Debug_Handle, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
#endif

///* 在此处修改，如果使用UART传输的其他API */
//#define UART_DEBUG_TRANSMIT()  HAL_UART_Transmit(UART_Debug_Handle, UART_Debug_Buff, UART_Debug_BuffIndex, 0xFFFF)
////#define UART_DEBUG_TRANSMIT()  HAL_UART_Transmit_DMA(UART_Debug_Handle, UART_Debug_Buff, UART_Debug_BuffIndex)
////#define UART_DEBUG_TRANSMIT()  HAL_UART_Transmit_IT(UART_Debug_Handle, UART_Debug_Buff, UART_Debug_BuffIndex)
//
//
///*
// * @brief  串口调试输出API，用法类似printf
// * @param  format  格式化字串
// * @param  ...  可变参数
// * @retval 无
// */
//void UART_Debug_Printf(const char *format, ...)
//{
//  /* 等待串口状态 */
//  while(UART_Debug_Handle->gState != HAL_UART_STATE_READY) ;
//
//  /* 初始缓存下标 */
//  UART_Debug_BuffIndex = 0;
//
//  /* 调用vprintf解析格式化字符串 */
//  va_list args_list;
//  va_start(args_list, format);
//  vprintf(format, args_list);
//  va_end(args_list);
//
//  UART_DEBUG_TRANSMIT();
//}
//
//
///*
// * @brief  调试输出的串口映射
// * @param  串口句柄
// * @retval 无
// */
//inline void UART_Debug_Remap(UART_HandleTypeDef *huart)
//{
//  UART_Debug_Handle = huart;
//}
//
//
///*
// * @brief  串口调试输出HAL status值
// * @param  HAL status
// * @retval 无
// */
//void UART_Debug_HAL_Status(HAL_StatusTypeDef status)
//{
//  switch (status) {
//  case HAL_OK:
//    UART_Debug_Printf("HAL_OK\r\n");
//    break;
//  case HAL_ERROR:
//    UART_Debug_Printf("HAL_ERROR\r\n");
//    break;
//  case HAL_BUSY:
//    UART_Debug_Printf("HAL_BUSY\r\n");
//    break;
//  case HAL_TIMEOUT:
//    UART_Debug_Printf("HAL_TIMEOUT\r\n");
//    break;
//  default:
//    UART_Debug_Printf("HAL_UNDEFINED\r\n");
//  }
//}


/* COED END UART_DEBUG */
