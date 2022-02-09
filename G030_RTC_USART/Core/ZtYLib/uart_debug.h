/*
 * uart_debug.h
 *
 *  Created on: Mar 9, 2020
 *      Author: AngBluCat
 */

#ifndef INC_UART_DEBUG_H_
#define INC_UART_DEBUG_H_

#include "stm32g0xx_hal.h"


void UART_Debug_Printf(const char* format, ...);
void UART_Debug_Remap(UART_HandleTypeDef *huart);
void UART_Debug_HAL_Status(HAL_StatusTypeDef status);

#endif /* INC_UART_DEBUG_H_ */
