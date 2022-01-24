/*
 * @Author: your name
 * @Date: 2021-12-24 15:34:36
 * @LastEditTime: 2022-01-21 10:39:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloGetNtp.h
 */
#ifndef _HOLOGETNTP_H
#define _HOLOGETNTP_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//NTP服务器地址
#define HOLONTPADDR "ntp.sjtu.edu.cn" //上海交大

void HoloConNtp(int timeOffset);    //连接NTP服务器
void HoloGetNtp(struct tm *pNtpTim);    //获取最新的时间

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_HOLOGETNTP_H