#ifndef     __STM32F4xx_H
#define     __STM32F4xx_H

#ifdef      __cplusplus
extern "C" {
#endif

#include    "core_cm4.h"
#include    <stdint.h>

typedef enum {
    RESET   = 0,
    SET     = !RESET
}FlagStatus, ITStatus;
typedef enum {
    DISABLE = 0,
    ENABLE  = !DISABLE
}FunctionalState;
#define     IS_FUNCTIONAL_STATE(STATE)          (((STATE) == DISABLE) || ((STATE) == ENABLE))

/**
 * @brief   CRC
 */
typedef struct {
    __IO    uint32_t    DR;    /* data */
    __IO    uint8_t     IDR;
            uint8_t     RESERVED0;
            uint16_t    RESERVED1;
    __IO    uint32_t    CR;
} CRC_TypeDef;

/**
 * @brief   RNG
 */
typedef struct {
    __IO    uint32_t    CR;
    __IO    uint32_t    SR;
    __IO    uint32_t    DR;
} RNG_TypeDef;

#define     PERIPH_BASE             ((uint32_t)0x40000000)
#define     AHB1PERIPH_BASE         (PERIPH_BASE + 0x20000)
#define     AHB2PERIPH_BASE         (PERIPH_BASE + 0x10000000)
#define     CRC_BASE                (AHB1PERIPH_BASE + 0x30000)
#define     RNG_BASE                (AHB2PERIPH_BASE + 0x60800)

#define     CRC                     ((CRC_TypeDef *) CRC_BASE)
#define     RNG                     ((RNG_TypeDef *) RNG_BASE)

/**
 * @brief   CRC
 */
#define     CRC_CR_RESET            ((uint8_t)0x01)

/**
 * @brief   RNG
 */
/**Bits definition for RNG_CR register*/
#define     RNG_CR_RNGEN            ((uint32_t)0x00000004)
#define     RNG_CR_IE               ((uint32_t)0x00000008)
/**Bits definition for RNG_SR register*/
#define     RNG_SR_DRDY             ((uint32_t)0x00000001)
#define     RNG_SR_CECS             ((uint32_t)0x00000002)
#define     RNG_SR_SECS             ((uint32_t)0x00000004)
#define     RNG_SR_CEIS             ((uint32_t)0x00000020)
#define     RNG_SR_SEIS             ((uint32_t)0x00000040)

#include    "stm32f4xx_conf.h"

#ifdef      __cplusplus
}
#endif

#endif      /*__STM32F4xx_H*/