/*
 * @Author: your name
 * @Date: 2021-12-24 15:37:41
 * @LastEditTime: 2021-12-27 11:21:20
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloConWifi.c
 */

#include "HoloConWifi.h"

const char *ssid = "Guests";    //wifi账号
const char *passWord = "tailin2019";    //wifi密码

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
    WiFi.begin(ssid, passWord);
    while (WL_CONNECTED != WiFi.status())
    {
        delay(500); //500ms
        DebugPrint(".");
    }
    
    DebugPrintln("");
    DebugPrintln("WiFi connected");        //连接成功
    DebugPrint("IP address: ");            //打印IP地址
    DebugPrintln(WiFi.localIP());
}
