/*******************************************************************************
 * 文件名：DCMotorEncoder.c
 * 内容摘要：编码器驱动程序
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "ADC_Filter.h"
#include "DCMotorEncoder.h"
#include "tim.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile int g_timx_encode_count = 0; /* 溢出次数 */
static ENCODE_TypeDef g_encode = {0}; /*编码器参数变量*/
static KFP g_motor_encoder_kfp = {0.2, 0, 0, 0, 0.1, 1};

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief 初始化编码器
 * @param  none
 * @retval none
 */
void dc_motor_encoder_init(void)
{
    //   MX_TIM3_Init();
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);
    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_IT_UPDATE); /* 清除更新中断标志位 */
    __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);  /* 使能更新中断 */

    HAL_TIM_Base_Start_IT(&htim16);
}

/**
 * @brief       获取编码器的值
 * @param       none
 * @retval      int 编码器值
 */
int gtim_get_encode(void)
{
    return (int32_t)__HAL_TIM_GET_COUNTER(&htim3) + g_timx_encode_count * 65536; /* 当前计数值+之前累计编码器的值=总的编码器值 */
}

/**
 * @brief       电机速度计算
 * @param       encode_now：当前编码器总的计数值
 *              ms：计算速度的间隔，中断1ms进入一次，例如ms = 5即5ms计算一次速度
 * @retval      none
 */
void speed_computer(int32_t encode_now, uint8_t ms)
{
    static uint8_t sp_count = 0;
    float speed = 0;

    if (sp_count == ms) /* 计算一次速度 */
    {
        /* 计算电机转速
           第一步 ：计算ms毫秒内计数变化量
           第二步 ；计算1min内计数变化量：g_encode.speed * ((1000 / ms) * 60 ，
           第三步 ：除以编码器旋转一圈的计数次数（倍频倍数 * 编码器分辨率）
           第四步 ：除以减速比即可得出电机转速
        */
        g_encode.encode_now = encode_now;                                                      /* 取出编码器当前计数值 */
        g_encode.speed = (g_encode.encode_now - g_encode.encode_old);                          /* 计算编码器计数值的变化量 */
        speed = (float)(g_encode.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO); /* 保存电机转速 */
        g_encode.encode_old = g_encode.encode_now;                                             /* 保存当前编码器的值 */

        g_motor_data.speed = kalmanFilter(&g_motor_encoder_kfp, speed);

        sp_count = 0;
    }
    sp_count++;
}

/**
 * @brief       定时器更新中断回调函数
 * @param        htim:定时器句柄指针
 * @note        此函数会被定时器中断函数共同调用的
 * @retval      无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3)) /* 判断CR1的DIR位 */
        {
            g_timx_encode_count--; /* DIR位为1，也就是递减计数 */
        }
        else
        {
            g_timx_encode_count++; /* DIR位为0，也就是递增计数 */
        }
    }

    if (htim->Instance == TIM16)
    {
        speed_computer(gtim_get_encode(), 50); /* 中位平均值滤除编码器抖动数据，50ms计算一次速度*/
    }
}
/* Private application code --------------------------------------------------*/
/**************DCMotorEncoder.c*************************************END OF FILE****/
