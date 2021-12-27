#include <SPI.h> //导入库
#include <TFT_eSPI.h>
#include "MyFont.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  tft.init(); //初始化
  tft.fillScreen(TFT_BLACK); //屏幕颜色
  tft.setCursor(10, 10, 1); //设置起始坐标(10, 10)，2 号字体
  tft.setTextColor(TFT_YELLOW); //设置文本颜色为白色
  tft.setTextSize(2); //设置文字的大小 (1~7)
  
  tft.println("TFT_Text"); //显示文字
  tft.fillCircle(30,30,10,TFT_BLUE); //画圆
  tft.drawLine(10,50, 118, 50, TFT_WHITE); //画线
  tft.drawPixel(70,70,TFT_RED); //画点
  tft.setTextColor(TFT_WHITE,TFT_BLUE); //设置文字颜色和背景颜色
  tft.setCursor(10, 80, 1); //设置起始坐标(10, 10)，2 号字体
  tft.println("TFT_Text"); //显示文字

  showMyFonts(40, 50, "周日晴", TFT_YELLOW); //在(40，50)处显示“周日晴”
}

void loop() {
  // put your main code here, to run repeatedly:
}

/*******************单个汉字显示****************/
void showMyFont(int32_t x, int32_t y, const char c[3], uint32_t color) 
{
  for (int k = 0; k < 25; k++)// 根据字库的字数调节循环的次数
  {
    if (hanzi[k].Index[0] == c[0] && hanzi[k].Index[1] == c[1] &&
    hanzi[k].Index[2] == c[2])
    {
      tft.drawBitmap(x, y, hanzi[k].hz_Id, hanzi[k].hz_width, 16,
      color);
    }
  }
}

/*******************整句汉字显示****************/
void showMyFonts(int32_t x, int32_t y, const char str[], uint32_t color) //显示整句汉字，字库比较简单，上下、左右输出是在函数内实现
{
  int x0 = x;
  for (int i = 0; i < strlen(str); i += 3) 
  {
    showMyFont(x0, y, str+i, color);
    x0 += 17;
  }
}
