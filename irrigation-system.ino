#include "utilities.h"
#include "wifi.h"

void connect(Wifi *wifi, bool setupFirst) {
  WifiReturnCode result = wifi->connect(setupFirst);
  switch(result) {
    case E_WIFI_SUCCESS:
      Serial.println("WIFI Success!");
      return;
    default:
      Serial.print("An unhandled error occurred. Code: ");
      Serial.println(result);
      //suspend();
  }
}

Wifi *wifi;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting WiFi");
  wifi = new Wifi();
  connect(wifi, false);
  wifi->disconnect();
}

void loop() {
}
