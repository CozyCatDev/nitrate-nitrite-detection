#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//—— pin definitions ——//
const int P1A = 26, P1B = 25;
const int P2A = 33, P2B = 32;
const int P3A = 27, P3B = 14;
const int motorPins[3][2] = {
  { P1A, P1B },
  { P2A, P2B },
  { P3A, P3B }
};

//relay
const int relay = 12;

//—— button ——//
const int buttonPin = 23;        // active-LOW with INPUT_PULLUP

//—— timing (ms) ——//
const unsigned long runTime     = 2000;   // each forward/backward run
const unsigned long interStep   =  500;   // gap between moves

//—— direction enum ——//
enum Direction { STOP=0, FORWARD=1, BACKWARD=2 };

void setup() {
  Serial.begin(115200);

  // OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // init motor pins
  for (uint8_t i = 0; i < 3; i++) {
    pinMode(motorPins[i][0], OUTPUT);
    pinMode(motorPins[i][1], OUTPUT);
  }
  
  // init relay
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  // init button
  pinMode(buttonPin, INPUT_PULLUP);

  stopAll();
}

void loop() {
  Serial.println("Ready. Waiting for button press…");
  displayCenteredText("Ready...");

  // wait for button press (LOW)
  while (digitalRead(buttonPin) == HIGH) {
    delay(10);
  }
  // simple debounce
  delay(50);
  // wait for release
  while (digitalRead(buttonPin) == LOW) {
    delay(10);
  }

  Serial.println("\n=== Button pressed! Beginning one full cycle ===");
  displayCenteredText("START...");

  // P1 forward → backward
  displayCenteredText("P1 -> FORWARD");
  motorControl(0, FORWARD, runTime);
  delay(interStep);

  displayCenteredText("P1 -> BACKWARD");
  motorControl(0, BACKWARD, runTime);
  delay(interStep);

  // P2 forward → backward
  displayCenteredText("P2 -> FORWARD");
  motorControl(1, FORWARD, runTime);
  delay(interStep);

  displayCenteredText("P2 -> BACKWARD");
  motorControl(1, BACKWARD, runTime);
  delay(interStep);

  // P3 forward → backward
  displayCenteredText("P3 -> FORWARD");
  motorControl(2, FORWARD, runTime);
  delay(interStep);

  displayCenteredText("P3 -> BACKWARD");
  motorControl(2, BACKWARD, runTime);

  vibrate();

  Serial.println("=== Cycle complete. Waiting for next button press…");
  displayCenteredText("Cycle complete...");
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

void vibrate(){
  digitalWrite(relay, LOW);
  Serial.println("Vibrating......");
  delay(3000);
  digitalWrite(relay, HIGH);
  delay(interStep);
}

void motorControl(uint8_t motorId, Direction dir, unsigned long durationMs) {
  stopAll();  // ensure no two motors run simultaneously
  if(dir != STOP) {Serial.print("P"); Serial.print(motorId); Serial.print(" -> ")};
  // set direction pins
  switch (dir) {
    case FORWARD:
      Serial.print("FORWARD");
      digitalWrite(motorPins[motorId][0], HIGH);
      digitalWrite(motorPins[motorId][1], LOW);
      break;
    case BACKWARD:
      Serial.print("BACKWARD");
      digitalWrite(motorPins[motorId][0], LOW);
      digitalWrite(motorPins[motorId][1], HIGH);
      break;
    case STOP:
    default:
      Serial.print("P"); Serial.print(motorId); Serial.println(" stopped.");
      digitalWrite(motorPins[motorId][0], LOW);
      digitalWrite(motorPins[motorId][1], LOW);
      return;  // nothing more to do
  }
  
  // run for given duration, then stop
  if (dir != STOP && durationMs > 0) {
    Serial.print(" for "); Serial.print(durationMs); Serial.println("ms");
    delay(durationMs);
    digitalWrite(motorPins[motorId][0], LOW);
    digitalWrite(motorPins[motorId][1], LOW);
    Serial.print("P"); Serial.print(motorId); Serial.println(" stopped.");
  }
}

void stopAll() {
  for (uint8_t i = 0; i < 3; i++) {
    digitalWrite(motorPins[i][0], LOW);
    digitalWrite(motorPins[i][1], LOW);
  }
  Serial.println("All motors stopped.");
}
