#include "oled_control.h"

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
  const String currentStage = motorId == 0 ? "SAMPLING" : motorId == 1 ? "DISSOLUTION" : motorId == 2 ? "DISPEL" : motorId == 3 ? "MIXING" : "NONE";
  // Measure the pixel bounds of the text
  int16_t x1, y1;
  uint16_t w, h;
  display.clearDisplay();
  display.getTextBounds(currentStage, 0, 0, &x1, &y1, &w, &h);

  int16_t textX = (SCREEN_WIDTH  - w) / 2 - x1;
  const int16_t textY = 0;  // top row

  int currentFrame = 0;

  unsigned long currentTime = millis();
  while(millis() - currentTime < screenDuration){
    display.clearDisplay();
    display.setCursor(textX, textY);
    display.print(currentStage);
    display.drawBitmap(48, 18, frames[currentFrame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    display.display();
    currentFrame = (currentFrame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
  }
  display.clearDisplay();
  display.display();
}