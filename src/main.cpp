#include <Arduino.h> 
#include <main.h> 
#include <OtaWrapper.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(9600); 
   pinMode(2, OUTPUT); 
  WiFiConnect::connect();
  WiFiScaner::scan(); 
  FileSysremInfo::info();
 
  // wserv.runFirmwareUpdater(true); 
  MDNS.begin("testservera");  
  Serial.printf("\nSlobodna memorija: %d\n", ESP.getFreeHeap());
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
}

void loop() {
  wserv.handleClient();
  MDNS.update();
  digitalWrite(2, !digitalRead(2));
  // delay(1000);
  // Serial.print(timeClient.getDay());
  // Serial.print("-");
  // Serial.println(timeClient.getFormattedTime());
  
}
