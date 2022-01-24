/*
 * @Author: your name
 * @Date: 2021-12-24 16:00:45
 * @LastEditTime: 2022-01-19 13:15:36
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\main.h
 */
#ifndef _MAIN_H
#define _MAIN_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _appServer_t
{
    QueueHandle_t xDispMsgQueue;
}appServer_t;

extern appServer_t appServer;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_MAIN_H