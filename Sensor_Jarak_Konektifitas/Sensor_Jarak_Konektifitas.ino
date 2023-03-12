#include "Wire.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
#define BUZZPIN D7                // Pin Buzzer
 
#define CM_ALERT_SOUND 10         // jarak minimal buzzer berbunyi
 
/* set SSID sensor parkir, tanpa password */
const char *ssid = "SensorParkir";
 

 

 
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  // Tunggu WiFi terhubung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tone(BUZZPIN, 4978);
    delay(100);
    noTone(BUZZPIN);
  }
 

}
 
void loop() {
 
  WiFiClient client;
  HTTPClient http;
 
  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://192.168.4.1/data")) {  // HTTP
 
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
 
        int jarak = payload.toInt();
        int bar = map(jarak, 0, 127, 127, 0);
 
        displayJarak(bar, jarak);
 
        if (jarak <= CM_ALERT_SOUND)            // bunyikan buzzer
          tone(BUZZPIN, 4978);
        else
          noTone(BUZZPIN);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
 
    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
 
  delay(100);
}
