#include "wifi.h"
#define CC3000_IRQ 3
#define CC3000_VBAT 5
#define CC3000_CS 10

Wifi::Wifi() {
  this->cc3000 = Adafruit_CC3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT, SPI_CLOCK_DIVIDER);
  this->connected = false;
}

Wifi::~Wifi() {
  if(this->connected) {

  }
}
