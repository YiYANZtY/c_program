/*******************************************************************************
 * 文件名：ADC_Filter.h
 * 内容摘要：
 * 其他说明：
 * 当前版本：
 * 作者：YiYANZtY
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADC_FILTER_H_
#define ADC_FILTER_H_
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
//卡尔曼滤波
typedef struct
{
    float LastP;//上次估算协方差 初始化值为0.02
    float Now_P;//当前估算协方差 初始化值为0
    float out;//卡尔曼滤波器输出 初始化值为0
    float Kg;//卡尔曼增益 初始化值为0
    float Q;//过程噪声协方差 初始化值为0.001
    float R;//观测噪声协方差 初始化值为0.543
} KFP;//Kalman Filter parameter

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint16_t xAvgFilter(uint16_t *pData,uint32_t xSize);

int iAvgFilter2(int array[], int size);

float kalmanFilter(KFP* kfp, float input);

int iSlidingFilter(int current);

/* Private defines -----------------------------------------------------------*/

#endif // ADC_FILTER_H_
/************ADC_Filter.h***************************************END OF FILE****/
