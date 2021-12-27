#include <WiFi.h> //wifi库
#include <ArduinoJson.h> //Json库
#include <HTTPClient.h> //HTTP库

const char* ssid = "Guests"; //wifi账号
const char* password = "tailin2019"; //wifi密码
const char* host = "api.seniverse.com"; //心知天气服务器地址
String now_address="",now_time="",now_temperature="";//用来存储报文得到的字符串
String now_weather = "";
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
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed"); //网络请求无响应打印连接失败
    return;
  }
  
  //URL请求地址
  String url ="/v3/weather/now.json?key=SXSAT941H1YjBNNe_&location=hangzhou&language=zh-Hans&unit=c";
  
  //发送网络请求
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
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

  // Stream& input;
  
  StaticJsonDocument<512> doc;

  deserializeJson(doc, jsonAnswer);

  JsonObject results_0 = doc["results"][0];
  
  JsonObject results_0_location = results_0["location"];
  const char* results_0_location_id = results_0_location["id"]; // "WTMKQ069CCJ7"
  const char* results_0_location_name = results_0_location["name"]; // "杭州"
  const char* results_0_location_country = results_0_location["country"]; // "CN"
  const char* results_0_location_path = results_0_location["path"]; // "杭州,杭州,浙江,中国"
  const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
  const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"
  
  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "晴"
  const char* results_0_now_code = results_0_now["code"]; // "0"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "14"
  
  const char* results_0_last_update = results_0["last_update"]; // "2021-12-23T16:48:22+08:00"
  
  now_address = results_0_location_name;
  now_weather = results_0_now_text;
  now_temperature = results_0_now_temperature;
  Serial.print("Now address:");
  Serial.println(now_address);
  Serial.print("Now weather:");
  Serial.println(now_weather);
  Serial.print("Now temperature:");
  Serial.println(now_temperature);

  delay(60 * 1000);
}
