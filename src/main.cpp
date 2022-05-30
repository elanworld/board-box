#include <Arduino.h>
#include <Common.h>
#include <FastLED.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <cJSON.h>

#define LED_PIN 19
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
String buffer;
cJSON* json;
cJSON* item;
int size;

IPAddress server(139, 155, 245, 132);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
}

char* byte2char(byte* var) {}

void setup() {
  // setupWifi();
  // PubSubClient client(server, ServerMqttPort, callback, wifiClient);
  // client.subscribe("test");
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);
  Serial.println("start");
}

void loop() {
  try {
    if (Serial.available() > 0) {
      buffer = Serial.readString();
      Serial.print("received: ");
      Serial.println(buffer);
      json = cJSON_Parse(buffer.c_str());
      size = cJSON_GetArraySize(json);
      for (size_t i = 0; i < size - 2; i += 3) {
        leds[i / 3] = CRGB(cJSON_GetArrayItem(json, i)->valueint,
                           cJSON_GetArrayItem(json, i + 1)->valueint,
                           cJSON_GetArrayItem(json, i + 2)->valueint);
      }
      FastLED.show();
    }
  } catch (...) {
    Serial.println("exception");
  }

  return;
}