#ifndef FRAMES_H
#define FRAMES_H

#include <Arduino.h>

#define FRAME_DELAY (42)
#define FRAME_WIDTH (32)
#define FRAME_HEIGHT (32)
#define FRAME_COUNT 28

extern const byte PROGMEM connectingWifiFrames[][128];
extern const byte PROGMEM samplingFrames[][128];
extern const byte PROGMEM addingSolutionFrames[][128];
extern const byte PROGMEM mixingFrames[][128];
extern const byte PROGMEM sendingDataFrames[][128];
extern const byte PROGMEM dispellingFrames[][128];

#endif