/*
 * @Author: your name
 * @Date: 2021-12-24 13:12:39
 * @LastEditTime: 2021-12-24 13:58:44
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32Touchpad\src\main.cpp
 */
#include <Arduino.h>

#define TOUCHEVENT 0

void TouchEvent();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

#if 1 == TOUCHEVENT
  //Pin:T0(GPIO4)
  touchAttachInterrupt(T0, TouchEvent, 40);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
#if 0 == TOUCHEVENT
  Serial.printf("touch:%d\r\n", touchRead(T0));
#endif
}

void TouchEvent()
{
  Serial.printf("Touch Event.\r\n");
}