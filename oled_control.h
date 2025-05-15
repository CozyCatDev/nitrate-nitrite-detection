#ifndef OLED_CONTROL_H
#define OLED_CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "macros.h"
#include "frames.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
extern Adafruit_SSD1306 display;
void initDisplay();
void displayCenteredText(const String &text);
void showAnimatedScreen(const byte frames[][128], const String &text, unsigned long screenDuration);

#endif