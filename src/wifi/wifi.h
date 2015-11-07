#ifndef WIFI_INCLUDED
#define WIFI_INCLUDED
#include "../../libraries/CC3000/Adafruit_CC3000.h"
#include <SPI.h>

class Wifi {
  private:
    Adafruit_CC3000 cc3000;
    bool connected;
};

#endif
