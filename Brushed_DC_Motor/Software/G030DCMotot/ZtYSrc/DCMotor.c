/*******************************************************************************
 * 文件名：DCMotor.c
 * 内容摘要：编码器驱动程序
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "DCMotor.h"
#include "tim.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* 停止引脚操作宏定义 
 * 此引脚控制H桥是否生效以达到开启和关闭电机的效果
 */
#define SHUTDOWN1_Pin                 GPIO_PIN_9
#define SHUTDOWN1_GPIO_Port           GPIOA

/* 电机开关，默认控制接口1 */
#define ENABLE_MOTOR    HAL_GPIO_WritePin(SHUTDOWN1_GPIO_Port,SHUTDOWN1_Pin,GPIO_PIN_SET)
#define DISABLE_MOTOR   HAL_GPIO_WritePin(SHUTDOWN1_GPIO_Port,SHUTDOWN1_Pin,GPIO_PIN_RESET)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Motor_TypeDef g_motor_data = {0}; /*电机参数变量*/

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief       电机初始化
 * @param       无
 * @retval      无
 */
void dcmotor_init(void)
{
//    MX_GPIO_Init();
//   MX_TIM1_Init();

    dcmotor_stop();                 /* 停止电机 */
    dcmotor_dir(0);                 /* 设置正转 */
    dcmotor_speed(0);               /* 速度设置为0 */
    // dcmotor_start();                /* 开启电机 */
}

/**
 * @brief       电机开启
 * @param       无
 * @retval      无
 */
void dcmotor_start(void)
{
    ENABLE_MOTOR;                                                       /* 拉高SD引脚，开启电机 */
}

/**
 * @brief       电机停止
 * @param       无
 * @retval      无
 */
void dcmotor_stop(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);          /* 关闭主通道输出 */
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);       /* 关闭互补通道输出 */
    DISABLE_MOTOR;                                                      /* 拉低SD引脚，停止电机 */
}

/**
 * @brief       电机旋转方向设置
 * @param       para:方向 0正转，1反转
 * @note        以电机正面，顺时针方向旋转为正转
 * @retval      无
 */
void dcmotor_dir(uint8_t para)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);          /* 关闭主通道输出 */
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);       /* 关闭互补通道输出 */

    if (para == 0)                /* 正转 */
    {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);     /* 开启主通道输出 */
    } 
    else if (para == 1)           /* 反转 */
    {
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);  /* 开启互补通道输出 */
    }
}

/**
 * @brief       电机速度设置
 * @param       para:比较寄存器值
 * @retval      无
 */
void dcmotor_speed(uint16_t para)
{
    if (para < (__HAL_TIM_GetAutoreload(&htim1) - 0x0F))  /* 限速 */
    {  
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, para);
    }
}

/**
 * @brief       电机控制
 * @param       para: pwm比较值 ,正数电机为正转，负数为反转
 * @note        根据传入的参数控制电机的转向和速度
 * @retval      无
 */
void motor_pwm_set(float para)
{
    int val = (int)para;

    if (val >= 0) 
    {
        dcmotor_dir(0);           /* 正转 */
        dcmotor_speed(val);
    } 
    else 
    {
        dcmotor_dir(1);           /* 反转 */
        dcmotor_speed(-val);
    }
}
/* Private application code --------------------------------------------------*/
/**************DCMotor.c*************************************END OF FILE****/
