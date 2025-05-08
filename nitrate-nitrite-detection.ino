#include "macros.h"
#include "secrets.h"
#include "init_wifi.h"
#include "motor_control.h"
#include "oled_control.h"
#include "thingspeak_control.h"

void setup() {
  Serial.begin(115200);
  
  // Set random seed using pin 0 so random values are different every time on startup
  randomSeed(analogRead(0));

  initWifi();
  initThingSpeak();
  initDisplay();
  initMotor();
  initRelay();
  initButton();
}

void loop() {
  Serial.println("Ready. Waiting for button press…");
  displayCenteredText("Ready...");

  // wait for button press (LOW)
  while (digitalRead(BUTTON_PIN) == HIGH) {
    delay(10);
  }
  // simple debounce
  delay(50);
  // wait for release
  while (digitalRead(BUTTON_PIN) == LOW) {
    delay(10);
  }

  Serial.println("\n=== Button pressed! Beginning one full cycle ===");
  displayCenteredText("START...");

  // P1 forward → backward
  displayCenteredText("P1 -> FORWARD");
  motorControl(0, FORWARD, PUMP_DURATION);
  delay(PUMP_DELAY);

  displayCenteredText("P1 -> BACKWARD");
  motorControl(0, BACKWARD, PUMP_DURATION);
  delay(PUMP_DELAY);

  // P2 forward → backward
  displayCenteredText("P2 -> FORWARD");
  motorControl(1, FORWARD, PUMP_DURATION);
  delay(PUMP_DELAY);

  displayCenteredText("P2 -> BACKWARD");
  motorControl(1, BACKWARD, PUMP_DURATION);
  delay(PUMP_DELAY);

  // P3 forward → backward
  displayCenteredText("P3 -> FORWARD");
  motorControl(2, FORWARD, PUMP_DURATION);
  delay(PUMP_DELAY);

  displayCenteredText("P3 -> BACKWARD");
  motorControl(2, BACKWARD, PUMP_DURATION);

  vibrate();

  Serial.println("=== Cycle complete. Waiting for next button press…");
  displayCenteredText("Cycle complete...");

  sendThingSpeakData();
}


