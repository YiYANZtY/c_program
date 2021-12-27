/*
 * @Author: your name
 * @Date: 2021-12-24 15:34:36
 * @LastEditTime: 2021-12-27 11:40:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloGetNtp.h
 */
#ifndef HOLOGETHTP_H
#define HOLOGETHTP_H

#include "main.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//NTP服务器地址
#define HOLONTPADDR "ntp.sjtu.edu.cn" //上海交大

void HoloConNtp(int timeOffset);    //连接NTP服务器
void HoloGetNtp(struct tm *ptm);    //获取最新的时间

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //HOLOGETHTP_H