#include "thingProperties.h"

#ifdef USE_ARDUINO_CLOUD
  float chipTemp = 0;
  float nitrateAbs = 0;
  float nitriteAbs = 0;
  bool isRunning = false;

  void initProperties(){

    ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
    ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
    ArduinoCloud.addProperty(chipTemp, READ, ON_CHANGE, NULL);
    ArduinoCloud.addProperty(nitrateAbs, READ, ON_CHANGE, NULL);
    ArduinoCloud.addProperty(nitriteAbs, READ, ON_CHANGE, NULL);
    ArduinoCloud.addProperty(isRunning, READWRITE, ON_CHANGE, NULL); // change NULL to onIsRunningChange if need callback function to run

  }

  WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASSWORD);
#endif