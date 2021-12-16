/*
 * WebSocketClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFiMulti.h>
#include <cJSON.h>
#include "Common.h"

WebSocketsClient webSocket;

typedef char unit8_t;

void digitalWriter(uint8_t* payload) {
  try {
    cJSON* res;
    res = cJSON_Parse(reinterpret_cast<char*>(payload));
    int switch1 = cJSON_GetObjectItem(res, "switch1")->valueint;
    digitalWrite(21, switch1);
  } catch (...) {
    Serial.println("parse data fail");
  }
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      webSocket.sendTXT("hello,i am board");
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      digitalWriter(payload);
      webSocket.sendTXT("got it!");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get bin: %s\n", payload);
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    default:
      Serial.printf("[WSc] get: %s\n", payload);
  }
}

void setup(int _) {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.printf("start...\n");
  pinMode(21, OUTPUT);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  setupWifi();

  // server address, port and URL
  webSocket.begin(ServerAddr, launchBoxPort, launchBoxWebSocketUrl);

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);
}

void loop(int _) { webSocket.loop(); }
