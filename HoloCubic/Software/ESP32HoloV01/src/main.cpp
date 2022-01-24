/*
 * @Author: your name
 * @Date: 2021-12-24 15:17:34
 * @LastEditTime: 2022-01-24 15:54:55
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\main.cpp
 */
#include "HoloCfg.h"
#include "TFT_eSPI.h"
#include "As.h"

struct tm ntpTim;
const int DAYNUMBER = 3;
zxtqWethr_t zxtqWethr[DAYNUMBER];
appServer_t appServer;
batState_t batState;

/* vTaskGetNtp to be created. */
void vTaskGetNtp( void * pvParameters );
/* vTaskDisplay to be created. */
void vTaskDisplay( void * pvParameters );
/* vTaskTouchPad to be created. */
void vTaskTouchPad( void * pvParameters );
/* vTaskGetWeather to be created. */
void vTaskGetWeather( void * pvParameters );
/* vTaskBatMan to be created. */
void vTaskBatMan( void * pvParameters );

void setup()
{
  BaseType_t xReturned;
  TaskHandle_t xGetNtpHandle = NULL;
  TaskHandle_t xDisplayHandle = NULL;
  TaskHandle_t xTouchPadHandle = NULL;
  TaskHandle_t xGetWeatherHandle = NULL;
  TaskHandle_t xBatManHandle = NULL;

  // put your setup code here, to run once:
  DebugBegin(115200);

  HoloDispInit();           //初始化屏幕
  HoloConnectWifi();        //连接wifi
  HoloConNtp(8 * 60 * 60);  //连接NTP服务器,第八时区
  HoloGetNtp(&ntpTim);      //获取最新的时间
  HoloBatInit();            ////初始化充电标志位IO和电压ADC_IO

  //创建显示消息队列
  appServer.xDispMsgQueue = xQueueCreate(10, sizeof(displayMessage_t));
  if( appServer.xDispMsgQueue == NULL )
  {
      /* Queue was not created and must not be used. */
      DebugPrintln("Creat xDispMsgQueue queue fail.");
  }

  /* 创建获取Ntp时间任务. */
  xReturned = xTaskCreate(
                  vTaskGetNtp,            /* Function that implements the task. */
                  "vTaskGetNtp",          /* Text name for the task. */
                  1024 * 4,               /* Stack size in words, not bytes. */
                  NULL,                   /* Parameter passed into the task. */
                  1,                      /* Priority at which the task is created. */
                  &xGetNtpHandle );       /* Used to pass out the created task's handle. */
  if( xReturned != pdPASS )
  {
    DebugPrintln("Creat vTaskGetNtp task fail.");
  }

  /* 创建显示任务 */
  xReturned = xTaskCreate(
                  vTaskDisplay,           /* Function that implements the task. */
                  "vTaskDisplay",         /* Text name for the task. */
                  1024 * 4,               /* Stack size in words, not bytes. */
                  NULL,                   /* Parameter passed into the task. */
                  1,                      /* Priority at which the task is created. */
                  &xDisplayHandle );      /* Used to pass out the created task's handle. */
  if( xReturned != pdPASS )
  {
    DebugPrintln("Creat vTaskDisplay task fail.");
  }

  /* 创建按键任务 */
  xReturned = xTaskCreate(
                  vTaskTouchPad,          /* Function that implements the task. */
                  "vTaskTouchPad",        /* Text name for the task. */
                  1024 * 4,               /* Stack size in words, not bytes. */
                  NULL,                   /* Parameter passed into the task. */
                  1,                      /* Priority at which the task is created. */
                  &xTouchPadHandle );     /* Used to pass out the created task's handle. */
  if( xReturned != pdPASS )
  {
    DebugPrintln("Creat vTaskTouchPad task fail.");
  }

  /* 创建获取天气信息任务 */
  xReturned = xTaskCreate(
                  vTaskGetWeather,          /* Function that implements the task. */
                  "vTaskGetWeather",        /* Text name for the task. */
                  1024 * 4,                 /* Stack size in words, not bytes. */
                  NULL,                     /* Parameter passed into the task. */
                  1,                        /* Priority at which the task is created. */
                  &xGetWeatherHandle );     /* Used to pass out the created task's handle. */
  if( xReturned != pdPASS )
  {
    DebugPrintln("Creat vTaskGetWeather task fail.");
  }

  /* 创建电池管理任务 */
  xReturned = xTaskCreate(
                  vTaskBatMan,              /* Function that implements the task. */
                  "vTaskBatMan",            /* Text name for the task. */
                  1024 * 4,                 /* Stack size in words, not bytes. */
                  NULL,                     /* Parameter passed into the task. */
                  1,                        /* Priority at which the task is created. */
                  &xBatManHandle );         /* Used to pass out the created task's handle. */
  if( xReturned != pdPASS )
  {
    DebugPrintln("Creat vTaskBatMan task fail.");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  delay(10);
}  

//调试函数
// HoloGetNtp(&ntpTim); //获取最新的时间
// HoloGetWeather(zxtqWethr, DAYNUMBER);
// HoloShowFont(0, 0, "晴", TFT_BLACK);
// HoloShowFonts(0, 17, "周一二三四五六日", TFT_YELLOW);
// HoloShowText(17, 17 * 2, 1, 2, TFT_BLUE, TFT_GREEN, "ABCDE abcde!");
// HoloShowTime(TFT_WHITE, TFT_BLACK, Astronaut, &ntpTim);
// HoloShowWethr(zxtqWethr, DAYNUMBER);
// HoloGetBatState(&batState);

//ADC函数
// analogRead(uint8_t pin);
// adc2_config_channel_atten();

/* vTaskGetNtp to be created. */
void vTaskGetNtp( void * pvParameters )
{

  for( ;; )
  {
    /* Task code goes here. */
    HoloGetNtp(&ntpTim); //获取最新的时间

    delay(1000);
  }
}

/* vTaskDisplay to be created. */
void vTaskDisplay( void * pvParameters )
{
  displayMessage_t tmpDispMsg, mainDispMsg = SHOW_TIME;
  displayMessage_t preMainDispMsg = SHOW_TIME, exDispMsg = SHOW_NONE;

  for( ;; )
  {
    /* Task code goes here. */
    //从队列中接收现在要显示的内容
    if(pdTRUE == xQueueReceive(appServer.xDispMsgQueue, &tmpDispMsg, 0))
    {
      //如果当前显示附加内容，则记录在exDispMsg中，mainDispMsg主要显示内容不变（显示天气还是时间）
      if((SHOW_TIME != tmpDispMsg) && (SHOW_WEATHER != tmpDispMsg))
      {
        exDispMsg = tmpDispMsg;
      }
      else
      {
        mainDispMsg = tmpDispMsg;
      }
      tmpDispMsg = SHOW_NONE;
    }

    //如果之前显示的内容和现在要显示的不同则清除一下屏幕
    if(preMainDispMsg != mainDispMsg)
    {
      HoloFillScreen(TFT_BLACK);
      preMainDispMsg = mainDispMsg;
    }

    switch (mainDispMsg)
    {
    case SHOW_TIME:
      HoloShowTime(TFT_WHITE, TFT_BLACK, Astronaut, &ntpTim);
      break;
    
    case SHOW_WEATHER:
      HoloShowWethr(zxtqWethr, DAYNUMBER);
      break;

    default:
      DebugPrintln("无法解释的显示信息。");
      HoloShowText(0, 0, 1, 1, TFT_BLACK, TFT_SKYBLUE, "Unexplained mainDispMsg.");
      break;
    }

    switch (exDispMsg)
    {
    case SHOW_NONE:
      break;

    case SHOW_BATCHARGE:
      HoloBatCharge();
      exDispMsg = SHOW_NONE;
      break;

    case SHOW_BATLOWPOW:
      HoloBatLowPow();
      break;

    default:
      DebugPrintln("无法解释附加的显示信息。");
      HoloShowText(0, 0, 1, 1, TFT_BLACK, TFT_SKYBLUE, "Unexplained exDispMsg.");
      break;
    }

    delay(100);
  }
}

/* vTaskTouchPad to be created. */
void vTaskTouchPad( void * pvParameters )
{
  uint8_t keyLock = 0, keyTimeCnt = 0, shortTouchFlg = 0;
  BaseType_t xStatus;
  displayMessage_t dispMsg = SHOW_TIME;

  for( ;; )
  {
    /* Task code goes here. */
    if (touchRead(T0) > 70)//没有按键按下
    {
      keyLock = 0;
      keyTimeCnt = 0;
      if (1 == shortTouchFlg)//之前短按现在没有按键按下
      {
        shortTouchFlg = 0;

        //下面代码执行短按情况
        DebugPrintln("Touch pad 短按");

        //发送SHOW_TIME给display任务显示时间
        dispMsg = SHOW_TIME;
        xStatus = xQueueSend(appServer.xDispMsgQueue, &dispMsg, 0);
        if(pdTRUE != xStatus)
        {
          DebugPrintln("Touch pad 短按信息发送失败");
        }
      }
    }
    else if(0 == keyLock)//有按键按下，且是第一次被按下
    {
      keyTimeCnt++;//累加定时中断次数
      if(keyTimeCnt > 1)
      {
        shortTouchFlg = 1;//激活按键短按的有效标志
      }
      if(keyTimeCnt > 15)
      {
        shortTouchFlg = 0;//清除按键短按的有效标志
        keyTimeCnt = 0;
        keyLock = 1;//自锁按键置位,避免一直触发

        //下面代码执行长按情况
        DebugPrintln("Touch pad 长按");

        //发送SHOW_WEATHER给display任务显示天气
        dispMsg = SHOW_WEATHER;
        xStatus = xQueueSend(appServer.xDispMsgQueue, &dispMsg, 0);
        if(pdTRUE != xStatus)
        {
          DebugPrintln("Touch pad 长按信息发送失败");
        }
      }
    }

    delay(100);
  }
}

/* vTaskGetWeather to be created. */
void vTaskGetWeather( void * pvParameters )
{

  for( ;; )
  {
    /* Task code goes here. */
    HoloGetWeather(zxtqWethr, DAYNUMBER); //获取最新的天气

    delay(30000);
  }
}

/* vTaskBatMan to be created. */
void vTaskBatMan( void * pvParameters )
{
  static float batThreshold = 4.13;
  BaseType_t xStatus;
  displayMessage_t dispMsg = SHOW_TIME;

  for( ;; )
  {
    /* Task code goes here. */
    HoloGetBatState(&batState);//电池管理

    //开始充电，现在充电并且之前没有充电
    if((BAT_CHARGE == batState.batChargeFlag) && (BAT_NO_CHARGE == batState.prvBatChargeFlag))
    {
        //发送SHOW_BATCHARGE给display任务提示开始充电
        dispMsg = SHOW_BATCHARGE;
        xStatus = xQueueSend(appServer.xDispMsgQueue, &dispMsg, 0);
        if(pdTRUE != xStatus)
        {
          DebugPrintln("开始充电显示信息发送失败");
        }
        
        DebugPrintln("Battery start charge.");
#if HOLOBATDEBUG
        HoloShowText(0, 20, 1, 1, 0xffff, 0x0000, (String) "Battery start charge.");
#endif //HOLOBATDEBUG
    }
    else if(BAT_CHARGE == batState.batChargeFlag)//充电状态，会一直进入
    {
#if HOLOBATDEBUG
        HoloShowText(0, 20, 1, 1, 0xffff, 0x0000, (String) "Battery is charging.");
#endif //HOLOBATDEBUG      
    }
    else if((BAT_NO_CHARGE == batState.batChargeFlag) && (BAT_CHARGE == batState.prvBatChargeFlag))//停止充电
    {
#if HOLOBATDEBUG
        HoloShowText(0, 20, 1, 1, 0xffff, 0x0000, (String) "Battery stop charge.");
#endif //HOLOBATDEBUG  
    }

    //电池缺电，会一直进入
    if((BAT_CHARGE != batState.batChargeFlag) && (batThreshold > batState.batPower))
    {
        batThreshold = 4.16;

        //发送SHOW_BATLOWPOW给display任务提示开始充电
        dispMsg = SHOW_BATLOWPOW;
        xStatus = xQueueSend(appServer.xDispMsgQueue, &dispMsg, 0);
        if(pdTRUE != xStatus)
        {
          DebugPrintln("低电量显示信息发送失败");
        }

        DebugPrintln("Battery low power.");
    }
    else//低电压迟滞比较，避免电压在阈值附近波动。
    {
        batThreshold = 4.16;
    }

    delay(1000);
  }
}
