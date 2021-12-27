#include <ESP8266WiFi.h>
#include <ArduinoJson.h> //Json库
#include <HttpClient.h> //HTTP库
//#include <ESP8266HTTPClient.h>

const char* ssid = "Guests"; //wifi账号
const char* password = "tailin2019"; //wifi密码
const char* host = "api.seniverse.com"; //心知天气服务器地址
String now_address="",now_time="",now_temperature="";//用来存储报文得到的字符串
const int httpPort = 80;
//URL请求地址
String url ="v3/weather/now.json?key=SXSAT941H1YjBNNe_&location=hangzhou&language=zh-Hans&unit=c";

void setup()
{
  Serial.begin(115200);
  // 连接网络
  WiFi.begin(ssid, password);
  //等待wifi连接
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); //连接成功
  Serial.print("IP address: "); //打印IP地址
  Serial.println(WiFi.localIP());
}

void loop()
{
  //创建TCP连接
  WiFiClient client;
    
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed"); //网络请求无响应打印连接失败
    return;
  }
  
  //发送网络请求
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(5000);
  
  //定义answer变量用来存放请求网络服务器后返回的数据
  String answer;
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    answer += line;
  }
  
  //断开服务器连接
  client.stop();
  Serial.println();
  Serial.println("closing connection");
  
  //获得json格式的数据
  String jsonAnswer;
  int jsonIndex;
  
  //找到有用的返回数据位置i 返回头不要
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
      jsonIndex = i;
      break;
    }
  }
  
  jsonAnswer = answer.substring(jsonIndex);
  Serial.println();
  Serial.println("JSON answer: ");
  Serial.println(jsonAnswer);
}
