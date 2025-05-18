#include "motor_control.h"

const int motorPins[3][2] = {
    { P1A, P1B },
    { P2A, P2B },
    { P3A, P3B }
};

void initMotor(){
    for (uint8_t i = 0; i < 3; i++) {
        pinMode(motorPins[i][0], OUTPUT);
        pinMode(motorPins[i][1], OUTPUT);
    }
    stopAll();
}

void initRelay(){
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}

void initButton(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// toggle vibration motor
void vibrate(){
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Vibrating......");
}

// toggle peristaltic pump in forward/backward direction for specific duration
void motorControl(uint8_t motorId, Direction dir) {
    // stopAll();  // ensure no two motors run simultaneously
    if(dir != STOP) {Serial.print("P"); Serial.print(motorId + 1); Serial.print(" -> ");}
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
        Serial.print("P"); Serial.print(motorId + 1); Serial.println(" stopped.");
        digitalWrite(motorPins[motorId][0], LOW);
        digitalWrite(motorPins[motorId][1], LOW);
        return;  // nothing more to do
    }

    if (dir != STOP) {Serial.print(" for "); Serial.print(motorId == 0 ? SAMPLING_DURATION : motorId == 1 ? MIXING_DURATION : motorId == 2 ? DISPELLING_DURATION : 0); Serial.println("ms");}
}

// stop all pumps
void stopAll() {
    for (uint8_t i = 0; i < 3; i++) {
        digitalWrite(motorPins[i][0], LOW);
        digitalWrite(motorPins[i][1], LOW);
    }
    Serial.println("All motors stopped.");
}