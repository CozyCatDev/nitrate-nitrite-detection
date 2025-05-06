#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

#define TOUCH_PIN 4

WiFiClient client;

void setup() {
  // Initialize serial, WiFi and ThingSpeak
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  // Set random seed using pin 0 so random values are different every time on startup
  randomSeed(analogRead(0));
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(SSID, PASSWORD);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Get touch and chip temperature values
  int touchVal = touchRead(TOUCH_PIN);
  float chipTemp = temperatureRead();

  // Generate random absorbance values
  float nitrateAbs = random(800,901) / 1000.0;
  float nitriteAbs = random(800,901) / 1000.0;

  // Print values to serial monitor
  Serial.print("Nitrate absorbance: ");
  Serial.print(nitrateAbs);
  Serial.print(", nitrite absorbance: ");
  Serial.print(nitriteAbs);
  Serial.print(", touch: ");
  Serial.print(touchVal);
  Serial.print(", temp: ");
  Serial.print(chipTemp);
  Serial.println("°C");
  
  // Set field values
  ThingSpeak.setField(1, nitrateAbs);
  ThingSpeak.setField(2, nitriteAbs);
  ThingSpeak.setField(3, touchVal);
  ThingSpeak.setField(4, chipTemp);

  // Write fields to ThingSpeak channel
  int httpCode = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }

  // Wait 20 seconds to update channel due to ThingSpeak's allowable update interval
  delay(20000);
}