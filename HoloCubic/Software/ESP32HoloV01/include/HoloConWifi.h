/*
 * @Author: your name
 * @Date: 2021-12-24 15:37:54
 * @LastEditTime: 2021-12-27 11:21:37
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloConWifi.h
 */
#ifndef HOLOCONWIFI_H
#define HOLOCONWIFI_H

#include "WiFi.h"
#include "HoloDbg.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern const char *ssid;     //wifi账号
extern const char *passWord; //wifi密码

void HoloConnectWifi(void); //连接wifi

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //HOLOCONWIFI_H