/*******************************************************************************
 * 文件名：RingBuffer.c
 * 内容摘要：环形队列FIFO接收数据
 * 其他说明：
 * 当前版本：V0101
 * 作者：YiYANZtY
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "ringbuffer.h"
#include <string.h>
#include <stddef.h>
#include <assert.h>

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define min(a,b) ( (a) < (b) )? (a):(b) 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
 * @brief 构造一个空环形缓冲区
 * @param  r 环形缓冲区控制块
 * @param  buf 给缓冲区分配的内存空间
 * @param  len 内存空间长度
 * @retval 非0表示成功
 */
int ring_buf_create(ring_buf_t *r, unsigned char *buf, unsigned int len)
{
    r->buf = buf;
    r->size = len;
    r->front = r->rear = 0;
    return buf == NULL;
}

/**
 * @brief 清空环形缓冲区
 * @param  r 环形缓冲区控制块
 * @retval NONE
 */
void ring_buf_clr(ring_buf_t *r)
{
    r->front = r->rear = 0;
}

/**
 * @brief 计算环形缓冲区容量 (字节为单位)
 * @param  r 环形缓冲区控制块
 * @retval 环形缓冲区中有效字节数 
 */
unsigned int ring_buf_len(ring_buf_t *r)
{
    return r->rear - r->front;
}

/**
 * @brief 将指定长度的数据放到环形缓冲区中
 * @param  r 环形缓冲区控制块
 * @param  buf 需要存入的数据指针
 * @param  len 需要存入的数据长度
 * @retval 实际放到中的数据
 */
unsigned int ring_buf_put(ring_buf_t *r, unsigned char *buf, unsigned int len)
{
    unsigned int i;
    unsigned int space;
    space = r->size + r->front - r->rear;
    len = min(len, space);                  /*得到实际写入的数据长度*/
    /*min(空闲空间大小,从real_in开始到缓冲区结尾的空间) -------------*/
    i = min(len, r->size - r->rear % r->size);
    /*
     * 当len > l时，拷贝buffer中剩余的内容
     *而剩余的大小为len - l 
     */
    memcpy(r->buf + r->rear % r->size, buf, i);
    memcpy(r->buf, buf + i, len - i);
    r->rear += len;
    return len;

}

/**
 * @brief 从环形缓冲区中读取指定长度的数据
 * @param  r 环形缓冲区控制块
 * @param  buf 输出数据缓冲区
 * @param  len 读取长度
 * @retval 实际读取长度
 */
unsigned int ring_buf_get(ring_buf_t *r, unsigned char *buf, unsigned int len)
{
    unsigned int i;
    unsigned int space;
    space = r->rear - r->front;
    len = min(len, space);
    i = min(len, r->size - r->front % r->size);
    memcpy(buf, r->buf + r->front % r->size, i);
    memcpy(buf + i, r->buf, len - i);
    r->front += len;
    return len;
}

/* Private application code --------------------------------------------------*/
/**************RingBuffer.c*************************************END OF FILE****/
