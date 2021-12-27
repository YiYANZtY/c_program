/*
 * @Author: your name
 * @Date: 2021-12-24 15:34:07
 * @LastEditTime: 2021-12-27 13:15:51
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloGetNtp.c
 */

#include "HoloGetNtp.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, HOLONTPADDR); //NTP服务器地址

/*******************************************************************************
 * 函数名称：HoloConNtp
 * 功能描述：连接到NTP服务器同步时间
 * 输入参数：无
 * 输出参数：无
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloConNtp(int timeOffset) //连接NTP服务器
{
    timeClient.begin();
    timeClient.setTimeOffset(timeOffset);
}

/*******************************************************************************
 * 函数名称：HoloGetNtp
 * 功能描述：获取最新的时间
 * 输入参数：无
 * 输出参数：ptm：获取的时间结构体指针
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloGetNtp(struct tm *ptm) //获取最新的时间
{
    char printStr[30];
    uint32_t epochTime;

    if (true != timeClient.update())
    {
        DebugPrintln("Ntp update false.");
    }

    epochTime = timeClient.getEpochTime();
    DebugPrint("Tpoch Time:");
    DebugPrintln(epochTime);

    memcpy(ptm, gmtime((time_t *)&epochTime), sizeof(*ptm));
    sprintf(printStr, "%d:%d:%d:%d:%d:%d:%d:", ptm->tm_year,
            ptm->tm_mon, ptm->tm_mday, ptm->tm_wday, ptm->tm_hour,
            ptm->tm_min, ptm->tm_sec);
    DebugPrintln(printStr);
}