/*
 * @Author: your name
 * @Date: 2021-12-24 15:37:41
 * @LastEditTime: 2022-01-21 17:08:44
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloConWifi.c
 */

#include "HoloCfg.h"
#include "WiFi.h"
#include "HoloDbg.h"

const char *ssid = "CMCC-7132";    //wifi账号
const char *passWord = "A71327132";    //wifi密码

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

    WiFi.begin(ssid, passWord);

    //尝试10秒没有连上wifi自动跳过
    while ( (WL_CONNECTED != WiFi.status()) && (20 > i))
    {
        delay(500); //500ms
        DebugPrint(".");
        i++;
    }
    
    DebugPrintln("");
    DebugPrintln("WiFi connected");        //连接成功
    DebugPrint("IP address: ");            //打印IP地址
    DebugPrintln(WiFi.localIP());
}
