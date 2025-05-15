#include "init_wifi.h"

void initWifi(){
    WiFi.mode(WIFI_STA);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID);
    while (WiFi.status() != WL_CONNECTED) {
        displayCenteredText("Connecting to WiFi");
        WiFi.begin(SSID, PASSWORD);
        Serial.print(".");
        delay(5000);
    }
    Serial.println("\nConnected.");
}