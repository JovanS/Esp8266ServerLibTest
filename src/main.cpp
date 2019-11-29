#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFiConnect.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <Ticker.h> 
#include <WebServer.h>
#include <filesystemInfo.h>
#include <DHT12.h>
// #include <DHTesp.h> 
// #include <dht.h>

DHT12 dht12;
WebServer wserv; 
Ticker ticker;
bool oled_print=false;
void printOLED();
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


WiFiUDP ntpUDP; 
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000); 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiConnect wifiConnector("iCraft","svastabre"); 

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C));
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("Booting...");
  display.display();
  timeClient.begin(); 
  dht12.begin(); 
  ticker.attach(1,[]() {
    oled_print=true;
  });
  
  FileSysmemInfo::info();
  MDNS.begin("4TINGZTermo");  
  wserv.runFirmwareUpdater(true); 
}

int i=1;
void loop() {
  wserv.handleClient();
  MDNS.update(); 
  delay(10); 
  printOLED();
}

char a=':'; 
void printOLED() {
  if(!oled_print) return;
  display.clearDisplay(); 
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  timeClient.update(); 
  display.printf("%02d", timeClient.getHours());
  (a==':' ? a=' ':a=':');
  display.print(a);
  display.printf("%02d\n", timeClient.getMinutes()); 
  display.printf("%2.1fC\n", dht12.readTemperature()); 
  display.setTextSize(1); 
  display.println();
  display.print(WiFi.localIP());
  display.print("  v0.003");
  display.display();
  oled_print=false;
  // DHT.read11(16);
}