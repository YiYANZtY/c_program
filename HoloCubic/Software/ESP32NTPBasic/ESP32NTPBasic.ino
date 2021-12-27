#include <NTPClient.h>
#include <WiFi.h> // for WiFi shield
#include <WiFiUdp.h>

const char *ssid = "Guests"; //wifi账号
const char *password = "tailin2019"; //wifi密码
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.sjtu.edu.cn"); //NTP服务器地址

void setup(){
  Serial.begin(115200);
  //连接wifi
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  timeClient.setTimeOffset(8*60*60);
}

void loop() {
  timeClient.update();
  //打印时间
  Serial.println(timeClient.getFormattedTime());
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  //打印时间
  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);
  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute);
  int weekDay = timeClient.getDay();
  Serial.print("Week Day: ");
  Serial.println(weekDay);
  //将epochTime换算成年月日
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);
  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  Serial.print("Year: ");
  Serial.println(ptm->tm_year);
  
  delay(1000);
}
