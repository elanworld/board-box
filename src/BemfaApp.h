/*
* 接入巴法云控制
* 智能语言控制控制，支持同时天猫、小爱、小度、google Assistent控制
* 也同时支持web控制、小程序控制、app控制，定时控制等
* 项目示例：通过发送on或off控制开关
* 官网：bemfa.com
*/

#include <WiFi.h>               //默认，加载WIFI头文件
#include "PubSubClient.h"              //默认，加载MQTT库文件
#include "Common.h"
#include "ApWifiConfig.h"

//********************需要修改的部分*******************//
const char* ssid = wifiSsid;           //修改，你的路由去WIFI名字
const char* password = wifiPasswd;     //你的WIFI密码
const char * ID_MQTT = bafaToken;     //用户私钥，控制台获取
const char*  topic = bafaTopic;        //主题名字，可在巴法云控制台自行创建，名称随意
const int gpio = switch001;       //单片机LED引脚值，D系列是NodeMcu引脚命名方式，其他esp8266型号将D2改为自己的引脚
//**************************************************//

const char* mqtt_server = "bemfa.com"; //默认，MQTT服务器
const int mqtt_server_port = 9501;      //默认，MQTT服务器
WiFiClient espClient;
PubSubClient client(espClient);

//灯光函数及引脚定义
void turnOnLed();
void turnOffLed();



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic:");
  Serial.println(topic);
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.print("Msg:");
  Serial.println(msg);
  if (msg == "on") {//如果接收字符on，亮灯
    turnOnLed();//开灯函数
  } else if (msg == "off") {//如果接收字符off，亮灯
    turnOffLed();//关灯函数
  }
  msg = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID_MQTT)) {
      Serial.println("connected");
      Serial.print("subscribe:");
      Serial.println(topic);
      //订阅主题，如果需要订阅多个主题，可发送多条订阅指令client.subscribe(topic2);client.subscribe(topic3);
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup(int _) {
  pinMode(gpio, OUTPUT); //设置引脚为输出模式
  apWifiConfig();           //设置wifi的函数，连接wifi
  client.setServer(mqtt_server, mqtt_server_port);//设置mqtt服务器
  client.setCallback(callback); //mqtt消息处理
  
}
void loop(int _) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

//打开灯泡
void turnOnLed() {
  Serial.println("high level");
  digitalWrite(gpio, HIGH);
}
//关闭灯泡
void turnOffLed() {
  Serial.println("low level");
  digitalWrite(gpio, LOW);
}
