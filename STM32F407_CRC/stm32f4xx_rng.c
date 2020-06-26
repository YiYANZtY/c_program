/*Includes*/
#include    "stm32f4xx_rng.h"

/**
 * @brief De-initializes the RNG peripheral registers to their default reset values.
 * @param None
 * @retval None
 */
void RNG_DeInit(void)
{
    //None
}

/**
 * @brief Enable or disable the RNG peripheral.
 * @param NewState: new state of the RNG peripheral.
 *                  This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RNG_Cmd(FunctionalState NewState)
{
    /*Check the parameters*/
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        RNG->CR |= RNG_CR_RNGEN;
    }
    else {
        RNG->CR &= ~RNG_CR_RNGEN;
    }
    
}

/**
 * @brief   Return a 32-bit random number.
 * @param   None
 * @retval  32-bit random number.
 */
uint32_t RNG_GetRandomNumber(void)
{
    return (RNG->DR);
}

/**
 * @brief   Enable or disable the RNG interrupt.
 * @param   NewState: new state of the RNG interrupt.
 * @retval  None
 */
void RNG_ITConfig(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        RNG->CR != RNG_CR_IE;
    }
    else {
        RNG->CR &= ~RNG_CR_IE;
    }
}

/**
 * @brief   Checks whether the specified RNG flag is set or reset.
 * @param   RNG_FLAG
 *          @arg    RNG_FLAG_DRDY
 *          @arg    RNG_FLAG_CECS
 *          @arg    RNG_FLAG_SECS
 * @retval  The new state of RNG_FLAG (SET or RESET).
 */
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG)
{
    FlagStatus bitstatus = RESET;

    assert_param(IS_RNG_GET_FLAG(RNG_FLAG));

    if ((RNG->SR & RNG_FLAG)!= (uint8_t)RESET) {
        bitstatus = SET;
    }
    else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief   Clears the RNG flags.
 * @param   RNG_FLAG
 *          @arg    RNG_FLAG_CECS
 *          @arg    RNG_FLAG_SECS
 * @retval  None
 */
void RNG_ClearFlag(uint8_t RNG_FLAG)
{
    assert_param(IS_RNG_CLEAR_FLAG(RNG_FLAG));

    RNG->SR &= ~(uint32_t)(((uint32_t)RNG_FLAG) << 4);
}

/**
 * @brief   Checks whether the specified RNG interrupt has occurred or not.
 * @param   RNG_IT
 *          @arg    
 *          @arg
 * @retval  The new state of the RNG_IT (SET or RESET).
 */
ITStatus RNG_GetITStatus(uint8_t RNG_IT)
{
    ITStatus bitstatus = RESET;

    assert_param(IS_RNG_GET_IT(RNG_IT));

    if ((RNG->SR & RNG_IT) != (uint8_t)RESET) {
        bitstatus = SET;
    }
    else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief   Clears the RNG interrupt pending bit(s).
 * @param   RNG_IT
 *          @arg    
 *          @arg
 * @retval  None
 */
void RNG_ClearITPendingBit(uint8_t RNG_IT)
{
    assert_param(IS_RNG_IT(RNG_IT));

    RNG->SR &= ~(uint8_t)RNG_IT;
}
