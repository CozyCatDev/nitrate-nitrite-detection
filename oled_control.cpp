#include "oled_control.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void displayCenteredText(const String &text) {
  display.clearDisplay();

  // Measure the pixel bounds of the text
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  // Compute top-left corner to center the text
  int16_t x = (SCREEN_WIDTH  - w) / 2 - x1;
  int16_t y = (SCREEN_HEIGHT - h) / 2 - y1;

  // Draw and refresh
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void showAnimatedScreen(uint8_t motorId, unsigned long screenDuration){
  const String currentStage = motorId == 0 ? "SAMPLING" : motorId == 1 ? "MIXING" : motorId == 2 ? "DISPEL" : "NONE";
  // Measure the pixel bounds of the text
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(currentStage, 0, 0, &x1, &y1, &w, &h);

  int16_t x = (SCREEN_WIDTH  - w) / 2 - x1;

  // horizontally center text and align to top
  display.setCursor(x, 0);

  int currentFrame = 0;

  unsigned long currentTime = millis();
  while(millis() - currentTime < screenDuration){
    display.clearDisplay();
    display.print(currentStage);
    display.drawBitmap(48, 18, frames[currentFrame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    currentFrame = (currentFrame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
  }
}