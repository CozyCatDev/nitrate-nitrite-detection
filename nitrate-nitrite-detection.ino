#include "macros.h"
#include "secrets.h"
#include "frames.h"
#ifdef USE_ARDUINO_CLOUD
  #include "thingProperties.h"
#endif
#include "init_wifi.h"
#include "motor_control.h"
#include "oled_control.h"
#include "iot_control.h"

void setup() {
  Serial.begin(115200);
  
  // Set random seed using pin 0 so random values are different every time on startup
  randomSeed(analogRead(0));
  initDisplay();
  initWifi();
  initIoT();
  initMotor();
  initRelay();
  initButton();
  
  // 31.5ml
  // 35.5
  // 35

  // 35 / 30 = 1.167 ml / s
  // 1.167 * (35-31.5) = 4.083s
}

void loop() {
  Serial.println("Ready. Waiting for button press…");
  displayCenteredText("Press Button");

  // wait for button press (LOW)
  while (digitalRead(BUTTON_PIN) == HIGH && !isRunning) {
    ArduinoCloud.update();
    delay(10);
  }
  // simple debounce
  if(!isRunning) {delay(50);}
  // wait for release
  while (digitalRead(BUTTON_PIN) == LOW && !isRunning) {
    delay(10);
  }

  Serial.println("\n=== Button pressed! Beginning one full cycle ===");

  // clean P1, P2, P3 tubes
  motorControl(0, BACKWARD);
  motorControl(1, BACKWARD);
  motorControl(2, BACKWARD);
  displayCenteredText("Cleaning");
  delay(CLEANING_DURATION);
  motorControl(0, STOP);
  motorControl(1, STOP);
  motorControl(2, STOP);
  delay(PUMP_DELAY);

  // sampling stage
  motorControl(0, FORWARD);
  showAnimatedScreen(samplingFrames, "SAMPLING", SAMPLING_DURATION);
  motorControl(0, STOP);
  delay(PUMP_DELAY);

  // add test solution stage
  motorControl(1, FORWARD);
  showAnimatedScreen(addingSolutionFrames, "ADD SOLUTION", ADDING_SOLUTION_DURATION);
  motorControl(1, STOP);
  delay(PUMP_DELAY);

  // mixing stage
  vibrate();
  showAnimatedScreen(mixingFrames, "MIXING", MIXING_DURATION);
  digitalWrite(RELAY_PIN, HIGH);
  delay(PUMP_DELAY);

  // send data to either ThingSpeak or Arduino Cloud
  sendIoTData();
  showAnimatedScreen(sendingDataFrames, "SENDING DATA", SENDING_DATA_DURATION);

  // dispel stage
  motorControl(2, FORWARD);
  showAnimatedScreen(dispellingFrames, "DISPELLING", DISPELLING_DURATION);
  motorControl(2, STOP);
  delay(PUMP_DELAY);

  Serial.println("=== Cycle complete. Waiting for next button press…");
  displayCenteredText("Cycle complete...");
  
  isRunning = false;
  ArduinoCloud.update();
}


