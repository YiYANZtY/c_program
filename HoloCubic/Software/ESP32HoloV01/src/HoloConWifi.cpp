/*
 * @Author: your name
 * @Date: 2021-12-24 15:37:41
 * @LastEditTime: 2022-01-26 16:27:09
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloConWifi.c
 */

#include "HoloCfg.h"
#include "WiFi.h"
#include "HoloDbg.h"

char ssid1[] = "YASHA-AD";          //wifi账号
char passWord1[] = "";      //wifi密码

char ssid2[] = "TP-LINK_4684";          //wifi账号
char passWord2[] = "bnm12345678";      //wifi密码

char ssid3[] = "CMCC-7132";          //wifi账号
char passWord3[] = "A71327132";      //wifi密码

char ssid4[] = "Guests";          //wifi账号
char passWord4[] = "tailin2019";      //wifi密码

char *pSsid = NULL;
char *pPassWord = NULL;

/*******************************************************************************
 * 函数名称：HoloConnectWifi
 * 功能描述：连接到Wifi
 * 输入参数：无
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloConnectWifi(void) //连接wifi
{
    int i = 0;

    //如果没有连接成功尝试其他密码
    i = 0;
    if(WL_CONNECTED != WiFi.status())
    {
        pSsid = ssid1;              //wifi账号
        pPassWord = passWord1;      //wifi密码

        WiFi.begin(pSsid, pPassWord);

        //尝试10秒没有连上wifi自动跳过
        while ( (WL_CONNECTED != WiFi.status()) && (200 > i))
        {
            HoloShowGif(Hammer, HAMMER_SIZE);

            delay(50); //50ms
            DebugPrint(".");
            i++;
        }
    }

    //如果没有连接成功尝试其他密码
    i = 0;
    if(WL_CONNECTED != WiFi.status())
    {
        pSsid = ssid2;              //wifi账号
        pPassWord = passWord2;      //wifi密码

        WiFi.begin(pSsid, pPassWord);

        //尝试10秒没有连上wifi自动跳过
        while ( (WL_CONNECTED != WiFi.status()) && (200 > i))
        {
            HoloShowGif(Hammer, HAMMER_SIZE);

            delay(50); //50ms
            DebugPrint(".");
            i++;
        }
    }

    //如果没有连接成功尝试其他密码
    i = 0;
    if(WL_CONNECTED != WiFi.status())
    {
        pSsid = ssid3;              //wifi账号
        pPassWord = passWord3;      //wifi密码

        WiFi.begin(pSsid, pPassWord);

        //尝试10秒没有连上wifi自动跳过
        while ( (WL_CONNECTED != WiFi.status()) && (200 > i))
        {
            HoloShowGif(Hammer, HAMMER_SIZE);

            delay(50); //50ms
            DebugPrint(".");
            i++;
        }
    }

    //如果没有连接成功尝试其他密码
    i = 0;
    if(WL_CONNECTED != WiFi.status())
    {
        pSsid = ssid4;              //wifi账号
        pPassWord = passWord4;      //wifi密码

        WiFi.begin(pSsid, pPassWord);

        //尝试10秒没有连上wifi自动跳过
        while ( (WL_CONNECTED != WiFi.status()) && (200 > i))
        {
            HoloShowGif(Hammer, HAMMER_SIZE);

            delay(50); //50ms
            DebugPrint(".");
            i++;
        }
    }

    for(i = 0; i < 30; i++)
    {
        HoloShowGif(Hammer, HAMMER_SIZE);

        delay(50); //50ms
    }
    
    DebugPrintln("");
    DebugPrintln("WiFi connected");        //连接成功
    DebugPrint("IP address: ");            //打印IP地址
    DebugPrintln(WiFi.localIP());
}
