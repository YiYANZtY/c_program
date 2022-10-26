/*******************************************************************************
 * 文件名：DCMotor.h
 * 内容摘要：编码器驱动程序
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DCMOTOR_H_
#define DCMOTOR_H_
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* 电机参数结构体 */
typedef struct
{
     uint8_t state;     /*电机状态*/
     float current;     /*电机电流*/
     float volatage;    /*电机电压*/
     float power;       /*电机功率*/
     float speed;       /*电机实际速度*/
     int32_t motor_pwm; /*设置比较值大小 */
} Motor_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define ROTO_RATIO                           (11 * 4) /* 线数*倍频系数，即11*4=44 */
#define REDUCTION_RATIO                      30  /* 减速比30:1 */

/* Exported macro ------------------------------------------------------------*/
extern Motor_TypeDef g_motor_data; /*电机参数变量*/

/* Exported functions prototypes ---------------------------------------------*/
extern void dc_motor_encoder_init(void);
extern int gtim_get_encode(void);

void dcmotor_init(void);
void dcmotor_start(void);
void dcmotor_stop(void);
void dcmotor_dir(uint8_t para);
void dcmotor_speed(uint16_t para);
void motor_pwm_set(float para);

/* Private defines -----------------------------------------------------------*/

#endif // DCMOTOR_H_
/************DCMotor.h***************************************END OF FILE****/
