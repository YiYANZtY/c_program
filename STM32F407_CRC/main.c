/**Includes*/
#include    "main.h"
#include    <stdio.h>

/**
 * @brief Main program
 * @param None
 * @retval None
 */
int main(void)
{
    RNG_Cmd(123);

    while (1) {
        /* code */
    }
    
}

#ifdef      USE_FULL_ASSERT

/**
 * @brief   Reports the name of the source file and the source line number
 *          where the assert_param error has occurred.
 * @param   file:pointer to the source file name..
 * @param   line:assert_param error line source number.
 * @retval  None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    printf("Error %s, %d\r\n", file, line);
    while (1) {
        /* code */
    }
    
}

#endif      /**USE_FULL_ASSERT*/



