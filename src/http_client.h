#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <cJSON.h>


WiFiMulti wifiMulti;


void setup(int _) {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();
    wifiMulti.addAP("PDCN", "248366796");

}

String isOn(int _) {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        // configure traged server and url
        http.begin("https://xianneng.top/api/leave-msg/github/action/last?userUni=alan");
        // start connection and send HTTP header
        int httpCode = http.GET();
        // httpCode will be negative on error
        if(httpCode > 0) {
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
                cJSON * res = cJSON_Parse(payload.c_str());
                cJSON * key =   cJSON_GetObjectItem(res,"cacheKey");
                Serial.println(key->valuestring);
                http.end();
                return key->valuestring;
            }

        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            setup();
        }
    }
    return "";
}