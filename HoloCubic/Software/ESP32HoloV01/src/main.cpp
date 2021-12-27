/*
 * @Author: your name
 * @Date: 2021-12-24 15:17:34
 * @LastEditTime: 2021-12-27 17:05:19
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\main.cpp
 */
#include "main.h"

struct tm pNtpTim;
const int DAYNUMBER = 3;
zxtqWethr_t zxtqWethr[DAYNUMBER];

void setup()
{
  // put your setup code here, to run once:
  DebugBegin(115200);
  Serial.begin(115200);

  HoloConnectWifi();       //连接wifi
  HoloConNtp(8 * 60 * 60); //连接NTP服务器,第八时区
}

void loop()
{
  // put your main code here, to run repeatedly:
  // HoloGetNtp(&pNtpTim); //获取最新的时间
  HoloGetWeather(zxtqWethr, DAYNUMBER);

  delay(1000);  //1000ms
}