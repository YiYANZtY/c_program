/*
 * uart_debug.c
 *
 *  Created on: Mar 9, 2020
 *      Author: AngBluCat
 */

#include "uart_debug.h"

/* COED BEGIN UART_DEBUG */

#include "usart.h"

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
//UART_HandleTypeDef *UART_Debug_Handle = &huart1;
UART_HandleTypeDef *UART_Debug_Handle = &huart2;

#ifdef __GNUC__

#else
#pragma import(__use_no_semihosting)      //不使用半主机模式
//标准库需要的支持函数                 
struct __FILE
{
  int handle;
};

typedef struct __FILE FILE;
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)
{
  x = x;
}
#endif

//如果使用printf函数请使用以下代码
PUTCHAR_PROTOTYPE
{
  //注意下面第一个参数是&husart1，因为cubemx配置了串口1自动生成的
  HAL_UART_Transmit(UART_Debug_Handle, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif

/* COED END UART_DEBUG */
