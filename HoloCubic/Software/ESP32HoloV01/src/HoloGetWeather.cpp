/*
 * @Author: your name
 * @Date: 2021-12-27 13:19:28
 * @LastEditTime: 2021-12-27 17:07:14
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\src\HoloGetWeather.cpp
 */
#include "HoloGetWeather.h"

const int httpPort = 80;
const char* host = "api.seniverse.com";  //心知天气服务器地址
const char* wethrScrtKey = "SXSAT941H1YjBNNe_"; //心知天气个人密钥
const char* wethrCity = "hangzhou"; //心知天气城市

/*******************************************************************************
 * 函数名称：HoloGetWeather
 * 功能描述：获取最新的天气。
 * 输入参数：size:有几天。
 * 输出参数：pZxtqWethr：保存天气的结构体数组。
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloGetWeather(zxtqWethr_t *pZxtqWethr, int size)
{
    WiFiClient client;

    if (!client.connect(host, httpPort))
    {
        DebugPrintln("Connect zhixintianqi failed.");
        return ;
    }

    //URL请求地址
    String url = String("/v3/weather/daily.json?key=") + wethrScrtKey + \
        "&location=" + wethrCity + "&language=zh-Hans&unit=c";
    //发送网络请求
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +\
        "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    
    delay(2000);

    String answer;
    while(client.available())
    {
      String line = client.readStringUntil('\r');
      answer += line;
    }

    //断开服务器连接
    client.stop();
    DebugPrintln("closing xinzhitianqi connection.");

    //分析json字符串
    HoloAnaWehtrJson(&answer, pZxtqWethr, size);

}

/*******************************************************************************
 * 函数名称：HoloAnaWehtrJson
 * 功能描述：解析知心天气的Json代码
 * 输入参数：pStr:需要转换的Json源码。
 *          size:有几天。
 * 输出参数：pZxtqWethr：保存天气的结构体数组。
 * 返回参数：无
 * 其他说明：无
*******************************************************************************/
void HoloAnaWehtrJson(String *pStr, zxtqWethr_t *pZxtqWethr, int size)
{
    //获得json格式的数据
    String jsonAnswer = "";
    int jsonIndex = 0;

    //找到有用的返回数据位置i 返回头不要
    for (int i = 0; i < pStr->length(); i++) 
    {
      if ((*pStr)[i] == '{') 
      {
        jsonIndex = i;
        break;
      }
    }
    jsonAnswer = pStr->substring(jsonIndex);
    DebugPrintln("JSON answer: ");
    DebugPrintln(jsonAnswer);

    // 提取Json中有关信息;
    StaticJsonDocument<1536> doc;
    deserializeJson(doc, jsonAnswer);

    JsonObject results_0 = doc["results"][0];

    int zxtqWethrIndex = 0;

    for (JsonObject results_0_daily_item : results_0["daily"].as<JsonArray>())
    {
        const char* results_0_daily_item_date = results_0_daily_item["date"]; // "2021-12-27", "2021-12-28", ...
        const char* results_0_daily_item_text_day = results_0_daily_item["text_day"]; // "多云", "多云", "多云"
        const char* results_0_daily_item_code_day = results_0_daily_item["code_day"]; // "4", "4", "4"
        const char* results_0_daily_item_text_night = results_0_daily_item["text_night"]; // "多云", "多云", "晴"
        const char* results_0_daily_item_code_night = results_0_daily_item["code_night"]; // "4", "4", "1"
        const char* results_0_daily_item_high = results_0_daily_item["high"]; // "4", "8", "12"
        const char* results_0_daily_item_low = results_0_daily_item["low"]; // "-2", "-1", "0"
        const char* results_0_daily_item_rainfall = results_0_daily_item["rainfall"]; // "0.00", "0.00", "0.00"
        const char* results_0_daily_item_precip = results_0_daily_item["precip"]; // "0.00", "0.00", "0.00"
        const char* results_0_daily_item_wind_direction = results_0_daily_item["wind_direction"]; // "无持续风向", ...
        const char* results_0_daily_item_wind_direction_degree = results_0_daily_item["wind_direction_degree"];
        const char* results_0_daily_item_wind_speed = results_0_daily_item["wind_speed"]; // "8.4", "8.4", ...
        const char* results_0_daily_item_wind_scale = results_0_daily_item["wind_scale"]; // "2", "2", "4"
        const char* results_0_daily_item_humidity = results_0_daily_item["humidity"]; // "41", "55", "62"

        pZxtqWethr[zxtqWethrIndex].date = results_0_daily_item_date;
        pZxtqWethr[zxtqWethrIndex].text_day = results_0_daily_item_text_day;
        pZxtqWethr[zxtqWethrIndex].code_day = results_0_daily_item_code_day;
        pZxtqWethr[zxtqWethrIndex].text_night = results_0_daily_item_text_night;
        pZxtqWethr[zxtqWethrIndex].code_night = results_0_daily_item_code_night;
        pZxtqWethr[zxtqWethrIndex].high = results_0_daily_item_high;
        pZxtqWethr[zxtqWethrIndex].low = results_0_daily_item_low;
        pZxtqWethr[zxtqWethrIndex].rainfall = results_0_daily_item_rainfall;
        pZxtqWethr[zxtqWethrIndex].precip = results_0_daily_item_precip;
        pZxtqWethr[zxtqWethrIndex].wind_direction = results_0_daily_item_wind_direction;
        pZxtqWethr[zxtqWethrIndex].wind_direction_degree = results_0_daily_item_wind_direction_degree;
        pZxtqWethr[zxtqWethrIndex].wind_speed = results_0_daily_item_wind_speed;
        pZxtqWethr[zxtqWethrIndex].wind_scale = results_0_daily_item_wind_scale;
        pZxtqWethr[zxtqWethrIndex].humidity = results_0_daily_item_humidity;
        zxtqWethrIndex++;
    }

    for (zxtqWethrIndex = 0; zxtqWethrIndex < size; zxtqWethrIndex++)
    {
        DebugPrint(pZxtqWethr[zxtqWethrIndex].date);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].text_day);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].code_day);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].text_night);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].code_night);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].high);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].low);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].rainfall);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].precip);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].wind_direction);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].wind_direction_degree);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].wind_speed);
        DebugPrint(pZxtqWethr[zxtqWethrIndex].wind_scale);
        DebugPrintln(pZxtqWethr[zxtqWethrIndex].humidity);
    }
}