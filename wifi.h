#ifndef WIFI_INCLUDED
#define WIFI_INCLUDED

#include <Adafruit_CC3000.h>
#include <SPI.h>

// Define error codes for this object. We are using Error codes instead of exception
// because we don't really care about the stack trace, and we want the errors to be as lightweight as possible.
#define E_WIFI_SUCCESS 0
#define E_WIFI_HARDWARE_ISSUE -1
#define E_WIFI_AP_NOT_FOUND -2;
#define E_WIFI_SC_NOT_FOUND -3;

typedef int WifiReturnCode;

class Wifi {
  private:
    Adafruit_CC3000 *cc3000;
    bool connected;
    WifiReturnCode initialize(bool setupFirst);
    WifiReturnCode initializeWithSetup();
    WifiReturnCode initializeWithoutSetup();
    WifiReturnCode configure();
    WifiReturnCode requestIP();
  public:
    Wifi();
    ~Wifi();
    WifiReturnCode connect(bool setupFirst);
    void disconnect();
};

#endif
