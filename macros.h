#ifndef MACROS_H
#define MACROS_H

// IoT platform to use
// #define USE_THINGSPEAK
#define USE_ARDUINO_CLOUD

// OLED dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// pin definitions
// #define TOUCH_PIN 4
#define RELAY_PIN 16
#define BUTTON_PIN 23

//3 -> 1
//1 -> 2
//
// motor driver pins, P2 and P3 pins reversed as they were installed in reverse
#define P1A 27
#define P1B 14
#define P2B 26
#define P2A 25
#define P3A 33
#define P3B 32

// duration values
#define CLEANING_DURATION 5000
#define SAMPLING_DURATION 42162 
#define ADDING_SOLUTION_DURATION 3090
#define MIXING_DURATION 3000
#define DISPELLING_DURATION 50000
#define SENDING_DATA_DURATION 5000
#define PUMP_DELAY 500
#define RESTART_DELAY 5000

//66.5ml per min
#endif