/*
 * @Author: your name
 * @Date: 2021-12-24 13:12:39
 * @LastEditTime: 2022-01-17 16:07:49
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32Touchpad\src\main.cpp
 */
#include <Arduino.h>

#define TOUCHEVENT 1

void TouchEvent();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

#if 1 == TOUCHEVENT
  //Pin:T0(GPIO4)
  touchAttachInterrupt(T0, TouchEvent, 70);
#endif
  pinMode(GPIO_NUM_19, OUTPUT);
  digitalWrite(GPIO_NUM_19, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
#if 0 == TOUCHEVENT
  Serial.printf("touch:%d\r\n", touchRead(T0));
#endif
  // pinMode(GPIO_NUM_19, OUTPUT);
  // digitalWrite(GPIO_NUM_19, HIGH);
}

void TouchEvent()
{
  Serial.printf("Touch Event.\r\n");
}