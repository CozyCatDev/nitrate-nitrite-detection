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

  // sampling stage
  motorControl(0, FORWARD);
  showAnimatedScreen(0, SAMPLING_DURATION);
  motorControl(0, STOP);
  delay(PUMP_DELAY);

  // add test solution stage
  motorControl(1, FORWARD);
  showAnimatedScreen(1, ADD_SOLUTION_DURATION);
  motorControl(1, STOP);
  delay(PUMP_DELAY);

  // mixing stage
  vibrate();
  showAnimatedScreen(3, MIXING_DURATION);
  digitalWrite(RELAY_PIN, HIGH);
  delay(PUMP_DELAY);

  sendThingSpeakData();

  // dispel stage
  motorControl(2, FORWARD);
  showAnimatedScreen(2, DISPEL_DURATION);
  motorControl(2, STOP);
  delay(PUMP_DELAY);

  Serial.println("=== Cycle complete. Waiting for next button press…");
  displayCenteredText("Cycle complete...");
}


