/*
  Common variable method
*/
#include <WiFi.h>  
#include "Common.h"

void setupWifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);
  WiFi.begin(wifiSsid, wifiPasswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}