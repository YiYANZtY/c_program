#ifndef _U8G2_PORT
#define _U8G2_PORT

#include "main.h"
#include "u8g2.h"

#define CONFIG_SCREEN_HEIGHT 64   // height of screen
#define CONFIG_SCREEN_WIDTH  128  // width of screen

#ifdef __cplusplus
extern "C" {
#endif

extern I2C_HandleTypeDef hi2c1;

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
    void *arg_ptr);
void u8g2Init(u8g2_t* u8g2);

#ifdef __cplusplus
}
#endif

#endif // _U8G2_PORT
