// Jovan Svorcan 22.11.2019
// under MIT licence
#ifndef WiFiConnect_h
#define WiFiConnect_h

#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h> 


extern "C" {
#include "user_interface.h"
}
  
WiFiEventHandler __wifiConnectHandler;
WiFiEventHandler __wifidisConnectHandler;
WiFiEventHandler __wifiGotIp;

class WiFiConnect {
    public:
           WiFiConnect(String ssid, String passwd) {
           WiFi.setOutputPower(14); 
           WiFi.mode(WIFI_STA); 
           // WiFi.setPhyMode(WIFI_PHY_MODE_11B); 
            WiFi.setAutoConnect(true);
            WiFi.setAutoReconnect(true);
            __wifiConnectHandler  = WiFi.onStationModeConnected(std::bind(&WiFiConnect::onConnect,this));
            __wifidisConnectHandler = WiFi.onStationModeDisconnected(std::bind(&WiFiConnect::onDisconnect,this));
            __wifiGotIp  = WiFi.onStationModeGotIP(std::bind(&WiFiConnect::onGotIp,this));
            WiFi.begin(ssid,passwd);  
        }

    void onGotIp() {
        Serial.println ( "WiFi On GotIp." );
        Serial.println(WiFi.localIP() ); 
        WiFi.printDiag(Serial);  
    }

    void onDisconnect(){
         Serial.println ( "WiFi On Disconnect." );   
    }

    void onConnect( ) {
        Serial.println ( "WiFi On Connect." );  
    }

     

};
#endif