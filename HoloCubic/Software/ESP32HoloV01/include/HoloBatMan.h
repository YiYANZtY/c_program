/*
 * @Author: your name
 * @Date: 2022-01-19 10:32:30
 * @LastEditTime: 2022-01-19 17:21:50
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloBatMan.h
 */
#ifndef _HOLOBATMAN_H
#define _HOLOBATMAN_H

#include <driver/adc.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

const int PIN_CHARGE = 33;
const adc1_channel_t ADC1_VBAT_CHANNEL = ADC1_CHANNEL_4;

//电压校准参数
const float vBatCaliK = (float) 3.9 / 4095 * 2;
const float vBatCaliB = (float) -0.3;

//电池是否充电
typedef enum _batCharge_t
{
    BAT_NO_CHARGE,
    BAT_CHARGE,
}batCharge_t;

//电池状态结构体
typedef struct _batState_t
{
    batCharge_t batChargeFlag;
    batCharge_t prvBatChargeFlag;
    float batPower;
}batState_t;

void HoloBatInit(void);//初始化充电标志位IO和电压ADC_IO
void HoloGetBatState(batState_t *batState);//获取电池状态

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_HOLOBATMAN_H