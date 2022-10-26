/*******************************************************************************
 * 文件名：RingBuffer.h
 * 内容摘要：环形队列FIFO接收数据
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/*环形缓冲区管理器*/
typedef struct
{
     unsigned char *buf;    /*环形缓冲区        */
     unsigned int size;     /*环形缓冲区        */
     unsigned int front;    /*头指针            */
     unsigned int rear;     /*尾指针            */
}ring_buf_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/*-------------------------外部接口声明----------------------------*/
 
int ring_buf_create(ring_buf_t *r,unsigned char *buf,unsigned int size);
 
void ring_buf_clr(ring_buf_t *r);
 
unsigned int ring_buf_len(ring_buf_t *r);
 
unsigned int ring_buf_put(ring_buf_t *r,unsigned char *buf,unsigned int len);
 
unsigned int ring_buf_get(ring_buf_t *r,unsigned char *buf,unsigned int len);

/* Private defines -----------------------------------------------------------*/

#endif // RINGBUFFER_H_
/************RingBuffer.h***************************************END OF FILE****/
