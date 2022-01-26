/*
 * @Author: your name
 * @Date: 2021-12-28 09:39:33
 * @LastEditTime: 2022-01-26 15:02:46
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloDisplay.cpp
 */

#include "HoloCfg.h"
#include "HoloYiYANFont.h"
#include "TFT_eSPI.h"
#include "SPI.h"
#include "HoloYiYANPic.h"

TFT_eSPI tft = TFT_eSPI();  //设定屏幕
String weekDays[] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};

/*******************************************************************************
 * 函数名称：HoloDispInit
 * 功能描述：初始化TFTLCD屏幕
 * 输入参数：无
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloDispInit(void)
{
  tft.init();                         //初始化显示寄存器
  tft.fillScreen(TFT_WHITE);          //屏幕颜色
  tft.setTextColor(TFT_BLACK);        //设置字体颜色黑色
  tft.setCursor(15, 30, 1);           //设置文字开始坐标(15,30)及1号字体
  tft.setTextSize(1);
  // tft.setRotation(4);//屏幕内容镜像显示或者旋转屏幕0-4  ST7735_Rotation中设置
  tft.setSwapBytes(true);             //使图片颜色由RGB->BGR

  tft.setRotation(4); //设置显示镜像 + 旋转90°

  //清除屏幕，显示黑色
  tft.fillScreen(TFT_BLACK);
}


/*******************************************************************************
 * 函数名称：HoloFillScreen
 * 功能描述：填充TFTLCD屏幕，用作清除屏幕。
 * 输入参数：bg:填充的颜色
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloFillScreen(uint16_t bg)
{
  tft.fillScreen(bg);
}

/*******************************************************************************
 * 函数名称：HoloShowFont
 * 功能描述：显示一个汉字
 * 输入参数：x:x坐标
 *          y:y坐标
 *          c[3]:字符utf-8编码
 *          color:颜色:TFT_BLACK
 * 输出参数：hanZiWidth:汉字的宽度
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloShowFont(int32_t x, int32_t y, const char c[3], uint32_t color, uint8_t *hanZiWidth)
{
  *hanZiWidth = 0;

  for (int k = 0; k < HANZISIZE; k++)// 根据字库的字数调节循环的次数
  {
    if (hanZi[k].Index[0] == c[0] && hanZi[k].Index[1] == c[1]\
        && hanZi[k].Index[2] == c[2])
    {
      tft.drawBitmap(x, y, hanZi[k].hzId, hanZi[k].hzWidth, hanZi[k].hzWidth, color, TFT_BLACK);
      *hanZiWidth = hanZi[k].hzWidth;
    }
  }
}

/*******************************************************************************
 * 函数名称：HoloShowFonts
 * 功能描述：显示整句汉字
 * 输入参数：x:x坐标
 *          y:y坐标
 *          str[]:字符串
 *          color:颜色:TFT_BLACK
 * 输出参数：无
 * 返回参数：无
 * 其他说明：显示整句汉字，字库比较简单，上下、左右输出是在函数内实现
*******************************************************************************/
void HoloShowFonts(int32_t x, int32_t y, const char str[], uint32_t color) 
{
  int x0 = x;
  uint8_t hanZiWidth = 0;
  for (int i = 0; i < strlen(str); i += 3) //utf-8编码使用3个字节编码汉字
  {
    HoloShowFont(x0, y, str+i, color, &hanZiWidth);
    x0 += hanZiWidth;
  }
}

/*******************************************************************************
 * 函数名称：HoloShowText
 * 功能描述：显示英文
 * 输入参数：x:x坐标
 *          y:y坐标
 *          font:字体:fontdata
 *          s:文本大小:范围0~7
 *          fg:文字颜色:TFT_BLACK
 *          bg:背景颜色:TFT_BLACK
 *          str:英文字符串
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloShowText(int16_t x, int16_t y, uint8_t font, uint8_t s,\
        uint16_t fg, uint16_t bg, const String str)
{
  //设置文本显示坐标，和文本的字体，默认以左上角为参考点，
    tft.setCursor(x, y, font);
  // 设置文本颜色为白色，文本背景黑色
    tft.setTextColor(fg, bg);
  //设置文本大小，文本大小的范围是1-7的整数
    tft.setTextSize(s);
  // 设置显示的文字，注意这里有个换行符 \n 产生的效果
    tft.println(str);
}

/*******************************************************************************
 * 函数名称：HoloShowTime
 * 功能描述：显示时间界面。显示日期、时间、图片
 * 输入参数：fg:文字颜色:TFT_BLACK
 *          bg:背景颜色:TFT_BLACK
 *          pGif:图片指针
 *          pNtpTim：获取的时间结构体指针
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloShowTime(uint16_t fg, uint16_t bg, const uint16_t **pGif, \
        struct tm *pNtpTim)
{
  String year, month, mDay, wDay, hour, minute, second;
  static int i = 0;

#ifdef HOLODISPDEBUG
  pNtpTim->tm_year  = 1;
  pNtpTim->tm_mon   = 1;
  pNtpTim->tm_mday  = 1;
  pNtpTim->tm_wday  = 0;
  pNtpTim->tm_hour  = 1;
  pNtpTim->tm_min   = 1;
  pNtpTim->tm_sec   = 1;
#endif
  
  //时间以1900年为基础所以需要加上
  year = String(pNtpTim->tm_year + 1900);

  //如果月份只有一位前面补0
  if (10 > (pNtpTim->tm_mon + 1))
  {
    month = "0" + String(pNtpTim->tm_mon + 1);
  }else
  {
    month = String(pNtpTim->tm_mon);
  }

  //如果日期只有一位前面补0
  if (10 > pNtpTim->tm_mday)
  {
    mDay = "0" + String(pNtpTim->tm_mday);
  }else
  {
    mDay = String(pNtpTim->tm_mday);
  }

  //如果小时只有一位前面补0
  if (10 > pNtpTim->tm_hour)
  {
    hour = "0" + String(pNtpTim->tm_hour);
  }else
  {
    hour = String(pNtpTim->tm_hour);
  }

  //如果分钟只有一位前面补0
  if (10 > pNtpTim->tm_min)
  {
    minute = "0" + String(pNtpTim->tm_min);
  }else
  {
    minute = String(pNtpTim->tm_min);
  }

  //如果秒钟只有一位前面补0
  if (10 > pNtpTim->tm_sec)
  {
    second = "0" + String(pNtpTim->tm_sec);
  }else
  {
    second = String(pNtpTim->tm_sec);
  }

  //获得星期的中文汉字然后从String转换为char *
  wDay = weekDays[pNtpTim->tm_wday];
  char cWeekDays[wDay.length() + 1];
  wDay.toCharArray(cWeekDays, wDay.length() + 1);

  //显示Gif图
  tft.pushImage(-3, 64, 64, 64, pGif[i]);
  i += 1;
  if(i>8)
  {
    i=0;
  }

  //显示水平线
  tft.drawFastHLine(10, 53, 108, TFT_WHITE);
  HoloShowText(7,       5,  6, 1, fg, bg, hour);
  HoloShowText(7 + 55,  5,  6, 1, TFT_ORANGE, bg, minute);
  HoloShowText(62,      65 + 0, 1, 2, fg, bg, month + "/" + mDay);
  HoloShowText(62,      65 + 20, 1, 1, fg, bg, year);
  HoloShowText(62 + 35, 65 + 20, 1, 2, fg, bg, second);
  //清除显示，显示星期
  // tft.fillRect(65, 100, 16 * 2, 16, TFT_BLACK);
  HoloShowFonts(78, 103, cWeekDays, TFT_VIOLET);
}

/*******************************************************************************
 * 函数名称：HoloShowWethr
 * 功能描述：显示天气界面
 * 输入参数：zxtqWethr:天气结构体
 *          dayNumb:有几天
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloShowWethr(const zxtqWethr_t *zxtqWethr, int dayNumb)
{
  const int leftBlank = 3;
  const int topBlank = 24;
  const int picInterval = 43;

  int humidity = 0;//降水概率
  const int humLen = 45;//表示降水概率的像素长度

  //显示地址
  HoloShowFonts(5, 0, "杭州", TFT_SILVER);

  //显示湿度
  humidity = zxtqWethr[0].humidity.toInt();
  tft.drawRoundRect(56, 15, humLen, 4, 2, TFT_WHITE);
  tft.drawFastHLine(56 + 2, 15 + 1, (humLen - 4) * humidity / 100, TFT_SKYBLUE);
  tft.drawFastHLine(56 + 2, 15 + 2, (humLen - 4) * humidity / 100, TFT_SKYBLUE);
  HoloShowText(103, 12, 1, 1, TFT_WHITE, TFT_BLACK, zxtqWethr[0].humidity + "%");

  //显示分隔线
  tft.drawFastVLine(leftBlank + picInterval * 1 - 7, topBlank + 6, 87, TFT_ORANGE);
  tft.drawFastVLine(leftBlank + picInterval * 2 - 7, topBlank + 6, 87, TFT_ORANGE);
  for(int j = 1; j <= 9; j++)
  {
    tft.drawFastHLine(0, topBlank + 12 + 2 + 30 + j, 128, TFT_ORANGE);
  }

  for (int i = 0; i < dayNumb; i++)
  {
    //显示白天天气文字
    HoloShowFonts(leftBlank + picInterval * i + 2, topBlank, 
      ppWetherText[zxtqWethr[i].code_day], TFT_WHITE);

    //显示白天天气图片
    tft.pushImage(leftBlank + picInterval * i, topBlank + 12 + 2, 
      30, 30, ppWetherPic[zxtqWethr[i].code_day]);

    //显示温度
    HoloShowText(leftBlank + 3 + picInterval * i, topBlank + 12 + 2 + 30 + 2, 
      1, 1, TFT_BLACK, TFT_ORANGE, (String) zxtqWethr[i].low + "~" + (String) zxtqWethr[i].high);

    //显示夜间天气图片
    tft.pushImage(leftBlank + picInterval * i, topBlank + 12 + 2 + 30 + 2 + 7 + 2,
      30, 30, ppWetherPic[zxtqWethr[i].code_night]);

    //显示夜间天气文字
    HoloShowFonts(leftBlank + picInterval * i + 2, topBlank + 12 + 2 + 30 + 2 + 7 + 2 + 30 + 2,
      ppWetherText[zxtqWethr[i].code_night], TFT_WHITE);
  }
}

/*******************************************************************************
 * 函数名称：HoloBatCharge
 * 功能描述：显示电池充电
 * 输入参数：无
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloBatCharge(void)
{
  for(int i = 0; i < 3; i++)
  {
    uint16_t color = TFT_BLACK;
    int dirct = 1;//0表示变暗,1表示变亮

    while( !((0 == dirct) && (0 == color)) )//颜色变暗并且最暗表示一次呼吸结束
    {
      color = color >> 5;
      
      //变亮过程中，如果最亮则改变方向慢慢变暗
      if(color >= (TFT_GREEN >> 5))
      {
        dirct = 0;
      }

      if(1 == dirct)
      {
        color += 0x4;
      }
      else
      {
        color -= 0x4;
      }  

      color = color << 5;

      //最终计算结果不能超过绿色最大值，不然就显示黑色。
      if(color >= TFT_GREEN)
      {
        tft.drawRect(0, 0, 128-7, 128-7, TFT_GREEN);
        tft.drawRect(1, 1, 126-7, 126-7, TFT_GREEN);
      }
      else
      {
        tft.drawRect(0, 0, 128-7, 128-7, color);
        tft.drawRect(1, 1, 126-7, 126-7, color);
      }

      delay(30);
    }
  }
}

/*******************************************************************************
 * 函数名称：HoloBatLowPow
 * 功能描述：显示低电量
 * 输入参数：无
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloBatLowPow(void)
{
  static uint16_t color = TFT_RED;
  static uint16_t decColor = 0;
  static int dirct = 0;

  color = ((TFT_RED >> 11) - decColor) << 11;

  if(decColor > (TFT_RED >> 11))
  {
    color = TFT_BLACK;
    dirct = 1;
  }
  else if(0x0 == decColor)
  {
    dirct = 0;
  }

  if(0 == dirct)
  {
    decColor += 0x4;
  }
  else
  {
    decColor -= 0x4;
  }  

  tft.drawRect(0, 0, 128-7, 128-7, color);
  tft.drawRect(1, 1, 126-7, 126-7, color);
}

/*******************************************************************************
 * 函数名称：HoloShowGif
 * 功能描述：显示Gif图片
 * 输入参数：pGif:图片指针
 *          size:有多少帧图片
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloShowGif(const uint16_t **pGif, int size)
{
  static int i = 0;

  //显示Gif图
  tft.pushImage(0, 0, 128, 128, pGif[i]);
  i += 1;
  if(i > (size - 1))
  {
    i = 0;
  }
}