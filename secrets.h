#ifndef SECRETS_H
#define SECRETS_H

#include "macros.h"

// Enter ThingSpeak channel credentials
#ifdef USE_THINGSPEAK
  #define CHANNEL_ID 1234
  #define WRITE_API_KEY "abcd"
#endif

// Enter WiFi credentials
extern const char SSID[];
extern const char PASSWORD[];
#ifdef USE_ARDUINO_CLOUD
  extern const char DEVICE_LOGIN_NAME[];
  extern const char DEVICE_KEY[];
#endif

#endif