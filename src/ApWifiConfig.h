#include <Arduino.h>
#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <Common.h>
#include <ESPAsyncWebServer.h>
#include <FileSystem.h>


AsyncWebServer server(80);

const char* wifiFile = "/wifiFile.txt";
const char* wifiPassFile = "/wifiPasswd.txt";

void notFound(AsyncWebServerRequest* request) {
  request->send(404, "text/plain", "Not found");
}

void apWifiConfig() {
  Serial.begin(115200);
  Serial.println();
  AsyncWebServer server(80);
  mountFs();
  if (checkFileExists(wifiFile)) {
    Serial.println("wifi config exists");
    setupWifi(read(wifiFile).c_str(), read(wifiPassFile).c_str());
  } else {
    const char* ap = "esp32-arduino";
    WiFi.softAP(ap);
    Serial.printf("start config wifi ap: %s\n", ap);
    String ip = WiFi.softAPIP().toString();
    Serial.printf("config page: %s\n", ip.c_str());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
      if (request->args() >= 2) {
        String wifiName = request->arg("wifiName");
        String password = request->arg("password");
        Serial.println();
        Serial.printf("wifi: %s %s", wifiName.c_str(), password.c_str());
        if (setupWifi(wifiName.c_str(), password.c_str())) {
          request->send_P(200, "text/plain", "wifi connected");
          write(wifiFile, wifiName.c_str());
          write(wifiPassFile, password.c_str());
        } else {
          request->send(200, "text/plain", "wifi fail");
        }
      }
      std::string page = R"(
<!DOCTYPE html>
<html>
    <body>

        <form action="http://192.168.4.1/">
        wifi Name:<br>
        <input type="text" name="wifiName">
        <br>
        password:<br>
        <input type="text" name="password">
        <br><br>
        <input type="submit" value="connect">
        </form> 
        </body>
</html>
)";
      request->send(200, "text/html", page.c_str());
    });
    server.onNotFound(notFound);
    server.begin();
  }
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  delay(10000);
  server.end();
  WiFi.softAPdisconnect(true);
  Serial.println();
  Serial.println("concect success");
}
