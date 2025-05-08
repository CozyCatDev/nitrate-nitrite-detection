#ifndef OLED_CONTROL_H
#define OLED_CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "macros.h"
#include "frames.h"

void initDisplay();
void displayCenteredText(const String &text);
void showAnimatedScreen(uint8_t motorId, unsigned long screenDuration);

#endif