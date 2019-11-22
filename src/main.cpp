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


