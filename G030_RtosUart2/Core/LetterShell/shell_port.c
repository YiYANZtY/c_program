/**
 * @brief shell移植到STM32L431时的接口实现
 * @author  mculover666
 * @date  2020/03/27
*/

#include "shell.h"
#include "usart.h"
#include "shell_port.h"

/* 1. 创建shell对象，开辟shell缓冲区 */
Shell shell;
char shell_buffer[125];


/* 2. 自己实现shell写函数 */
#if 1
/**
 * @brief shell读取数据函数原型
 *
 * @param data shell读取的字符
 * @param len 请求读取的字符数量
 *
 * @return unsigned short 实际读取到的字符数量
 */
signed short UserShellRead(char *data, unsigned short len)
{
  if (HAL_UART_Receive(&huart2, (uint8_t *)data, len, 200) == HAL_OK)
  {
    return len;
  }
  return 0;
}

/**
 * @brief shell写数据函数原型
 *
 * @param data 需写的字符数据
 * @param len 需要写入的字符数
 *
 * @return unsigned short 实际写入的字符数量
 */
signed short UserShellWrite(char *data, unsigned short len)
{
  if (HAL_UART_Transmit(&huart2, (uint8_t *)data, len, 200) == HAL_OK)
  {
    return len;
  }
  return 0;
}

#else
/**
 * @brief shell写数据函数原型
 *
 * @param data 需写的字符数据
 * @param len 需要写入的字符数
 *
 * @return unsigned short 实际写入的字符数量
 */
signed short UserShellWrite(char *data, unsigned short len)
{
  if (HAL_UART_Transmit(&huart2, (uint8_t *)data, len, 200) == HAL_OK)
  {
    return len;
  }
  return 0;
}
#endif

/* 3. 编写初始化函数 */
void User_Shell_Init(void)
{
  //注册自己实现的写函数
  shell.write = UserShellWrite;
  shell.read = UserShellRead;

  //调用shell初始化函数
    shellInit(&shell, shell_buffer, 125);
}
