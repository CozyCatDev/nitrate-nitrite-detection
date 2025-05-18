#include "init_wifi.h"

void initWifi(){
    int currentFrame = 0;
    const String text = "Connecting to WiFi";
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int16_t textX = (SCREEN_WIDTH  - w) / 2 - x1;
    const int16_t textY = 0;
    WiFi.mode(WIFI_STA);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(SSID, PASSWORD);
      display.clearDisplay();
      display.setCursor(textX, textY);
      display.print(text);
      display.drawBitmap(48, 18, connectingWifiFrames[currentFrame], FRAME_WIDTH, FRAME_HEIGHT, 1);
      display.display();
      currentFrame = (currentFrame + 1) % FRAME_COUNT;
      delay(FRAME_DELAY);
    }
    display.clearDisplay();
    display.display();
    Serial.println("\nConnected.");
}