/*
  Common variable method
*/
#include <WiFi.h>  

#define wifiSsid "PDCN"
#define wifiPasswd "248366796"
#define bafaToken "843ac2ca8da440278224ed13a7e06ccb"
#define bafaTopic "switch"
#define gpio21 21
#define ServerAddr "139.155.245.132"
#define launchBoxPort 8030
#define launchBoxWebSocketUrl "/board"

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