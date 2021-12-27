#include <SPI.h> //导入库
#include <TFT_eSPI.h>
#include "As.h"

TFT_eSPI tft = TFT_eSPI();
int i = 0;

void setup() {
  // put your setup code here, to run once:
  tft.init(); //初始化

}

void loop(){
  tft.setSwapBytes(true); //使图片颜色由RGB->BGR
  tft.pushImage(10, 55, 64, 64, Astronaut[i]); // (10,55) 显示 64 × 64像素的图片
  delay(100); //延时
  i+=1; //下一帧
  if(i>8){i=0;}
}
