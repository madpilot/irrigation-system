#include "utilities.h"
#include "wifi.h"
#include <Adafruit_CC3000.h>
#include <CC3000_MDNS.h>

#define CC3000_IRQ 3
#define CC3000_VBAT 5
#define CC3000_CS 10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT, SPI_CLOCK_DIVIDER);
MDNSResponder mdns;

void connect(Adafruit_CC3000 &cc3000, bool setupFirst) {
  wifi_return_code result = wifi_connect(cc3000, setupFirst);
  switch(result) {
    case E_WIFI_SUCCESS:
      Serial.println("WIFI Success!");
      return;
    default:
      Serial.print("An unhandled error occurred. Code: ");
      Serial.println(result);
      while(1);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting WiFi");

  connect(cc3000, true);

  int attempts = 5;
  while(!mdns.begin("sprinklers", cc3000) && attempts-- > 0) {
    Serial.println(F("Error setting up MDNS responder!"));
  }

  if(attempts == 0) {
    while(1);
  }
}

void loop() {
  mdns.update();
}
