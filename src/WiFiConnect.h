// Jovan Svorcan 22.11.2019
// under MIT licence
#ifndef WiFiConnect_h
#define WiFiConnect_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

class WiFiConnect {
    public:
        static void connect() {
           WiFi.setOutputPower(18); 
            WiFi.setPhyMode(WIFI_PHY_MODE_11N);
            wifiMulti.addAP("iCraft", "svastabre");   

            Serial.println("\nConnecting: ");
            while (wifiMulti.run() != WL_CONNECTED) {  
                delay(100);
                Serial.print('.');
            }
            
            Serial.println('\n');
            Serial.print("Connected to ");
            Serial.println(WiFi.SSID());              
            Serial.print("IP address:\t");
            Serial.println(WiFi.localIP() ); 
        }
};
#endif