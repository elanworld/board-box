/*
  Common variable method
*/
#include "Common.h"

#include <WiFi.h>

void setupWifi() { setupWifi(wifiSsid, wifiPasswd); }

bool setupWifi(const char* ssid, const char* passwd) {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, passwd);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    count++;
    delay(500);
    Serial.print(".");
    if (count > 20) {
      Serial.println();
      Serial.printf("fail to connect: |%s|%s|\n", ssid, passwd);
      return false;
    }
  }
  Serial.println();
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
  return true;
}

