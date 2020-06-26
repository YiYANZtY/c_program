/*Define to prevent recursive inclusion*/
#ifndef     __STM32F4xx_CONF_H
#define     __STM32F4xx_CONF_H

#ifdef      __cplusplus
extern "C" {
#endif      /*__cplusplus*/

/**Includes*/
#include    "stm32f4xx_crc.h"
#include    "stm32f4xx_rng.h"

/**Uncomment the line below to expanse the "assert_param" macro in the 
 * Standard Peripheral Library drivers code
 */
#define     USE_FULL_ASSERT

/*Exported macro*/
#ifdef      USE_FULL_ASSERT
    /**
     * @brief The assert_param macro is used for funtion's parameters check.
     * @param expr: If expr is false, it calls assert_failed function
     *              which reports the name of the source file and the source
     *              line number of the call that failed.
     *              If expr is ture, it returns no value.
     * @retval None
     */
    #define     assert_param(expr)  ((expr) ? (void)0 : \
                                    assert_failed((uint8_t *)__FILE__, __LINE__))
    /**Exported functions*/
    void assert_failed(uint8_t* file, uint32_t line);
#else
    #define     assert_param(expr)  ((void)0)
#endif      /*USE_FULL_ASSERT*/

#ifdef      __cplusplus
}
#endif      /*__cplusplus*/

#endif      /*__STM32F4xx_CONF_H*/