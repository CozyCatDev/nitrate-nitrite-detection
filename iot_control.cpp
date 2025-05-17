#include "iot_control.h"

#ifdef USE_THINGSPEAK
  WiFiClient client;
#endif

void initIoT(){
  #ifdef USE_THINGSPEAK
    ThingSpeak.begin(client);
  #elif defined(USE_ARDUINO_CLOUD)
    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
    
    /*
      The following function allows you to obtain more information
      related to the state of network and IoT Cloud connection and errors
      the higher number the more granular information you’ll get.
      The default is 0 (only errors).
      Maximum is 4
  */
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
  #endif
}

void sendIoTData(){
  // Get touch and chip temperature values
  // int touchVal = touchRead(TOUCH_PIN);
  chipTemp = temperatureRead();

  // Generate random absorbance values
  nitrateAbs = random(800,901) / 1000.0;
  nitriteAbs = random(800,901) / 1000.0;

  // Print values to serial monitor
  Serial.print("Nitrate absorbance: ");
  Serial.print(nitrateAbs);
  Serial.print(", nitrite absorbance: ");
  Serial.print(nitriteAbs);
  // Serial.print(", touch: ");
  // Serial.print(touchVal);
  Serial.print(", temp: ");
  Serial.print(chipTemp);
  Serial.println("°C");

  #ifdef USE_THINGSPEAK
    // Set field values
    ThingSpeak.setField(1, nitrateAbs);
    ThingSpeak.setField(2, nitriteAbs);
    // ThingSpeak.setField(3, touchVal);
    ThingSpeak.setField(4, chipTemp);

    // Write fields to ThingSpeak channel
    int httpCode = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

    if (httpCode == 200) {
      Serial.println("Channel write successful.");
    }
    else {
      Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
    }
  #elif defined(USE_ARDUINO_CLOUD)
    ArduinoCloud.update();
  #endif
}