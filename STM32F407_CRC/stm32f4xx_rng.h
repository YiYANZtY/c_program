/*Define to prevent recursive inclusion*/
#ifndef     __STM32F4xx_RNG_H
#define     __STM32F4xx_RNG_H

#ifdef      __cplusplus
extern "C" {
#endif      /*__cplusplus*/

/*Includes*/
#include    "stm32f4xx.h"

/**
 * @defgroup    RNG_flags_definition
 */
#define     RNG_FLAG_DRDY           ((uint8_t)0x01)
#define     RNG_FLAG_CECS           ((uint8_t)0x02)
#define     RNG_FLAG_SECS           ((uint8_t)0x04)

#define     IS_RNG_GET_FLAG(RNG_FLAG)           ( \
                                                ((RNG_FLAG) == RNG_FLAG_DRDY) || \
                                                ((RNG_FLAG) == RNG_FLAG_CECS) || \
                                                ((RNG_FLAG) == RNG_FLAG_SECS) \
)
#define     IS_RNG_CLEAR_FLAG(RNG_FLAG)         ( \
                                                ((RNG_FLAG) == RNG_FLAG_CECS) || \
                                                ((RNG_FLAG) == RNG_FLAG_SECS) \
)

/**
 * @defgroup    RNG_interrupts_definition
 */
#define     RNG_IT_CEI              ((uint8_t)0x20)
#define     RNG_IT_SEI              ((uint8_t)0x40)

#define     IS_RNG_GET_IT(RNG_IT)               ( \
                                                ((RNG_IT) == RNG_IT_CEI) || \
                                                ((RNG_IT) == RNG_IT_SEI) \
)
#define     IS_RNG_IT(RNG_IT)                   ( \
                                                ((RNG_IT) & (uint8_t)0x9F == 0x00) && \
                                                ((RNG_IT) != 0x00) \
)

/*Exported functions*/
/*Function used to set the RNG configuration to the default reset state*/
void RNG_DeInit(void);

/*Configuration function*/
void RNG_Cmd(FunctionalState NewState);

/*Get 32 bit Random number function*/
uint32_t RNG_GetRandomNumber(void);

/*Interrupt and flags management functions*/
void RNG_ITConfig(FunctionalState NewState);
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG);
void RNG_ClearFlag(uint8_t RNG_FLAG);
ITStatus RNG_GetITStatus(uint8_t RNG_IT);
void RNG_ClearITPendingBit(uint8_t RNG_IT);

#ifdef      __cplusplus
}
#endif      /*__cplusplus*/

#endif      /*__STM32F4xx_RNG_H*/