#include <Arduino.h> 
#include <main.h> 


void setup() {
  Serial.begin(9600); 
   
  WiFiConnect::connect();
  WiFiScaner::scan();
  // wifiScan(); 
  FileSysremInfo::info();
 
  wserv.runFirmwareUpdater(true); 
  MDNS.begin("testservera");
}

void loop() {
  wserv.handleClient();
  MDNS.update();
}

void wifiScan() {
  // Serial.println("\n\nNetwork scan");
  // int n = WiFi.scanNetworks(false, true);
  // String ssid;
  // uint8_t encryptionType;
  // int32_t RSSI;
  // uint8_t* BSSID;
  // int32_t channel;
  // bool isHidden;

  // for (int i = 0; i < n; i++)
  // {
  //   WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
  //   Serial.printf("%d: %s, Ch:%d (%ddBm) %s %s\n", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
  // }
  // Serial.println();
}



