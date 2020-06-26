#ifndef __STM32F4xx_CRC_H
#define __STM32F4xx_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif  /*__STM32F4xx_CRC_H*/