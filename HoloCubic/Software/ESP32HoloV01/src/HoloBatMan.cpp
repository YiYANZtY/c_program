/*
 * @Author: your name
 * @Date: 2022-01-19 10:33:09
 * @LastEditTime: 2022-01-21 15:32:57
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloBatMan.c
 */

#include "HoloCfg.h"

// /*******************************************************************************
//  * 函数名称：HoloBatInit
//  * 功能描述：初始化电池检测的IO口
//  * 输入参数：无
//  * 输出参数：无
//  * 返回参数：无
//  * 其他说明：无
// *******************************************************************************/
void HoloBatInit(void)
{
    //SET PIN_CHARGE input up.判断是否是充电状态。
    pinMode(PIN_CHARGE, INPUT_PULLUP);

    // initialize ADC.ADC电压采集引脚。
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_VBAT_CHANNEL, ADC_ATTEN_11db);//150~2450mV
}

// /*******************************************************************************
//  * 函数名称：HoloGetBatState
//  * 功能描述：获取电池状态
//  * 输入参数：无
//  * 输出参数：batState:电池状态结构体指针
//  * 返回参数：无
//  * 其他说明：无
// *******************************************************************************/
void HoloGetBatState(batState_t *batState)
{
    //更新电池充电标志位状态
    batState->prvBatChargeFlag = batState->batChargeFlag;

    //获取充电标志位
    if(0 == digitalRead(PIN_CHARGE))
    {
        batState->batChargeFlag = BAT_CHARGE;
    }
    else
    {
        batState->batChargeFlag = BAT_NO_CHARGE;
    }

    //获取电压值
    batState->batPower = (float) adc1_get_raw(ADC1_VBAT_CHANNEL) * vBatCaliK + vBatCaliB;

#if HOLOBATDEBUG
    DebugPrintln(batState->batChargeFlag);
    DebugPrintln(batState->batPower);
    HoloShowText(0, 0, 1, 1, 0xffff, 0x0000, (String) batState->batChargeFlag);
    HoloShowText(0, 10, 1, 1, 0xffff, 0x0000, (String) batState->batPower);
#endif //HOLOBATDEBUG
}

// /*******************************************************************************
//  * 函数名称：HoloSearchMid
//  * 功能描述：获取数组中值的下标
//  * 输入参数：data:需要滤波的数组
//             size:数组长度
//  * 输出参数：无
//  * 返回参数：数组中值的下标
//  * 其他说明：无
// *******************************************************************************/
int HoloSearchMid(uint16_t data[], int size)
{
    int i, j, flag;
    uint16_t tmp;
    for(i = size - 1; i >= 0; i--)
    {
        flag = 0;
        for(j = 0; j < i; j++)
        {
            if(data[j] > data[j + 1])
            {
                tmp = data[j];
                data[j] = data[j+1];
                data[j + 1] = tmp;
                flag++;
            }
        }
        if(flag == 0)
        break;
    }
    if(size % 2)
        return size / 2 + 1;
    else
        return size / 2;
}