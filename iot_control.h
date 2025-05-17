#ifndef IOT_CONTROL_H
#define IOT_CONTROL_H

#include <Arduino.h>
#include <WiFi.h>
#include "macros.h"
#include "secrets.h"
#ifdef USE_THINGSPEAK
  #include "ThingSpeak.h"
#elif defined(USE_ARDUINO_CLOUD)
  #include "thingProperties.h"
#endif

void initIoT();
void sendIoTData();

#endif