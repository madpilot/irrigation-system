#include "wifi.h"
#define CC3000_IRQ 3
#define CC3000_VBAT 5
#define CC3000_CS 10
#define CC3000_DEVICE_NAME "CC3000"

#define WLAN_SECURITY   WLAN_SEC_WPA2

Wifi::Wifi(void) {
  this->cc3000 = new Adafruit_CC3000(CC3000_CS, CC3000_IRQ, CC3000_VBAT, SPI_CLOCK_DIVIDER);
  this->connected = false;
}

Wifi::~Wifi(void) {
  if(this->connected) {
    this->cc3000->disconnect();
  }
}

WifiReturnCode Wifi::initializeWithSetup() {
  Serial.println("Initializing With Setup");
  if(this->cc3000->begin(false)) {
    return this->configure();
  }
  return E_WIFI_HARDWARE_ISSUE;
}

WifiReturnCode Wifi::initializeWithoutSetup() {
  Serial.println("Initializing Without Setup");
  if(this->cc3000->begin(false, true, CC3000_DEVICE_NAME)) {
    return E_WIFI_SUCCESS;
  }
  return E_WIFI_HARDWARE_ISSUE;
}

WifiReturnCode Wifi::initialize(bool setupFirst) {
  Serial.println("Initializing");
  if(setupFirst) {
    return this->initializeWithSetup();
  } else {
    return this->initializeWithoutSetup();
  }
}

WifiReturnCode Wifi::configure() {
  Serial.println("Starting Smart Config");
  if (cc3000->startSmartConfig(CC3000_DEVICE_NAME)) {
    return E_WIFI_SUCCESS;
  } else {
    return E_WIFI_SC_NOT_FOUND;
  }
}

WifiReturnCode Wifi::requestIP() {
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  Serial.println("Requesting an IP");
  while (!cc3000->checkDHCP()) {
    delay(100);
  }


  cc3000->getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv);
  Serial.println("\nIP Addr: ");
  cc3000->printIPdotsRev(ipAddress);
  return E_WIFI_SUCCESS;
}

WifiReturnCode Wifi::connect(bool setupFirst) {
  Serial.println("Connecting");
  if(this->connected) {
    return E_WIFI_SUCCESS;
  }

  WifiReturnCode returnCode = this->initialize(setupFirst);
  if(returnCode != E_WIFI_SUCCESS) {
    return returnCode;
  }

  this->connected = true;
  return this->requestIP();
}

void Wifi::disconnect() {
  if(this->connected) {
    this->cc3000->disconnect();
    this->connected = false;
  }
}
