/*
 * @Author: your name
 * @Date: 2021-12-27 13:19:43
 * @LastEditTime: 2022-01-25 16:08:38
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloGetWeather.h
 */
#ifndef _HOLOGETWEATHER_H
#define _HOLOGETWEATHER_H

#include "WString.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _zxtqWethr_t
{
    String  date;                     //日期
    String  text_day;                 //白天天气现象文字
    int     code_day;                 //白天天气现象代码
    String  text_night;               //晚间天气现象文字
    int     code_night;               //晚间天气现象代码
    int     high;                     //当天最高温度
    int     low;                      //当天最低温度
    String  rainfall;                 //降水概率，范围0~100，单位百分比（目前仅支持国外城市）
    String  precip;                   //风向文字
    String  wind_direction;           //风向角度，范围0~360
    String  wind_direction_degree;    //风速，单位km/h（当unit=c时）、mph（当unit=f时）
    String  wind_speed;               //风力等级
    String  wind_scale;               //降水量，单位mm
    String  humidity;                 //相对湿度，0~100，单位为百分比
}zxtqWethr_t;

void HoloGetWeather(zxtqWethr_t *pZxtqWethr, int size);
void HoloAnaWehtrJson(String *pStr, zxtqWethr_t *pZxtqWethr, int size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_HOLOGETWEATHER_H