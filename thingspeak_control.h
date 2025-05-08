#ifndef THINGSPEAK_CONTROL_H
#define THINGSPEAK_CONTROL_H

#include <Arduino.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include "macros.h"
#include "secrets.h"

void initThingSpeak();
void sendThingSpeakData();

#endif