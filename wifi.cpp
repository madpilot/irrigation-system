#include "wifi.h"
#define CC3000_DEVICE_NAME "CC3000"

// Hidden internal functions
wifi_return_code initialize_without_setup(Adafruit_CC3000 &cc3000);
wifi_return_code initialize_with_setup(Adafruit_CC3000 &cc3000);
wifi_return_code initialize(Adafruit_CC3000 &cc3000, bool setup_first);
wifi_return_code configure(Adafruit_CC3000 &cc3000);
wifi_return_code request_ip(Adafruit_CC3000 &cc3000);

wifi_return_code initialize_with_setup(Adafruit_CC3000 &cc3000) {
  Serial.println("Initializing With Setup");
  if(cc3000.begin(false)) {
    return configure(cc3000);
  }
  return E_WIFI_HARDWARE_ISSUE;
}

wifi_return_code initialize_without_setup(Adafruit_CC3000 &cc3000) {
  Serial.println("Initializing Without Setup");
  if(cc3000.begin(false, true, CC3000_DEVICE_NAME)) {
    return E_WIFI_SUCCESS;
  }
  return E_WIFI_HARDWARE_ISSUE;
}

wifi_return_code initialize(Adafruit_CC3000 &cc3000, bool setup_first) {
  Serial.println("Initializing");
  if(setup_first) {
    return initialize_with_setup(cc3000);
  } else {
    return initialize_without_setup(cc3000);
  }
}

wifi_return_code configure(Adafruit_CC3000 &cc3000) {
  Serial.println("Starting Smart Config");
  if (cc3000.startSmartConfig(CC3000_DEVICE_NAME)) {
    return E_WIFI_SUCCESS;
  } else {
    return E_WIFI_SC_NOT_FOUND;
  }
}

wifi_return_code request_ip(Adafruit_CC3000 &cc3000) {
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  Serial.println("Requesting an IP");
  while (!cc3000.checkDHCP()) {
    delay(100);
  }


  cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv);
  Serial.print("IP Addrress");
  cc3000.printIPdotsRev(ipAddress);
  Serial.print("\n");
  return E_WIFI_SUCCESS;
}

wifi_return_code wifi_connect(Adafruit_CC3000 &cc3000, bool setup_first) {
  wifi_return_code return_code = initialize(cc3000, setup_first);
  if(return_code != E_WIFI_SUCCESS) {
    return return_code;
  }

  return request_ip(cc3000);
}
