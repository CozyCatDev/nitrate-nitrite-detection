#include "thingspeak_control.h"

WiFiClient client;

void initThingSpeak(){
  ThingSpeak.begin(client);
}

void sendThingSpeakData(){
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
}