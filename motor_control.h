#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "macros.h"

enum Direction { STOP=0, FORWARD=1, BACKWARD=2 };
void initMotor();
void initRelay();
void initButton();
void vibrate();
void motorControl(uint8_t motorId, Direction dir, unsigned long durationMs);
void stopAll();

#endif