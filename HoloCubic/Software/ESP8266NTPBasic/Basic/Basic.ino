#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "Guests";  //wifi账号
const char *password = "tailin2019";  //wifi密码

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.sjtu.edu.cn"); //ntp服务器地址,上海交大

void setup(){
  Serial.begin(115200);

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
  
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time:");
  Serial.println(epochTime);

  int currentHour = timeClient.getHours();
  Serial.print("Hour:");
  Serial.println(currentHour);

  int currentMinute = timeClient.getMinutes();
  Serial.print("Mintes:");
  Serial.println(currentMinute);

  int weekDay = timeClient.getDay();
  Serial.print("Week Day:");
  Serial.println(weekDay);

  struct tm *ptm = gmtime((time_t *)&epochTime);
  
  int monthDay = ptm->tm_mday;
  Serial.print("Month Day:");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon + 1;
  Serial.print("Month:");
  Serial.println(currentMonth);

  int currentYear = ptm->tm_year + 1900;
  Serial.print("Year:");
  Serial.println(currentYear);

//  int currentSec = ptm->tm_sec;
//  Serial.print("sec:");
//  Serial.println(currentSec);
//
//  int currentMin = ptm->tm_min;
//  Serial.print("Min:");
//  Serial.println(currentMin);
//
//  currentHour = ptm->tm_hour;
//  Serial.print("Year:");
//  Serial.println(currentHour);
  
//  Serial.print(timeClient.getFormattedTime());

  delay(1000);
}
