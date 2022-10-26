/*******************************************************************************
 * 文件名：DCMotorEncoder.h
 * 内容摘要：编码器驱动程序
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
 *******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DCMOTOR_ENCODER_H_
#define DCMOTOR_ENCODER_H_
/* Includes ------------------------------------------------------------------*/
#include "DCMotor.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* 编码器参数结构体 */
typedef struct
{
     int encode_old; /* 上一次计数值 */
     int encode_now; /* 当前计数值 */
     float speed;    /* 编码器速度 */
} ENCODE_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void dc_motor_encoder_init(void);
int gtim_get_encode(void);

/* Private defines -----------------------------------------------------------*/

#endif // DCMOTOR_ENCODER_H_
/************DCMotorEncoder.h***************************************END OF FILE****/
