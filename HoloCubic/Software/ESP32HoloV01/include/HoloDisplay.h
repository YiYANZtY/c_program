/*
 * @Author: your name
 * @Date: 2021-12-28 09:39:46
 * @LastEditTime: 2022-01-21 15:40:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloDisplay.h
 */
#ifndef _HOLODISPLAY_H
#define _HOLODISPLAY_H

#include "HoloGetWeather.h"
#include "stdint.h"
#include "WString.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//显示内容消息队列
typedef enum _displayMessage_t
{
    SHOW_NONE,
    SHOW_TIME,
    SHOW_WEATHER,
    SHOW_BATCHARGE,
    SHOW_BATLOWPOW,
    DIP_MSG_MAX,
}displayMessage_t;

void HoloDispInit(void);
void HoloShowFont(int32_t x, int32_t y, const char c[3], uint32_t color, uint8_t hanZiWidth);
void HoloShowFonts(int32_t x, int32_t y, const char str[], uint32_t color);
void HoloShowText(int16_t x, int16_t y, uint8_t font, uint8_t s,
        uint16_t fg, uint16_t bg, const String str);
void HoloShowTime(uint16_t fg, uint16_t bg, const uint16_t **pGif,
        struct tm *pNtpTim);
void HoloShowWethr(const zxtqWethr_t *zxtqWethr, int dayNumb);
void HoloFillScreen(uint16_t bg);
void HoloBatCharge(void);
void HoloBatLowPow(void);
        
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_HOLODISPLAY_H