// Jovan Svorcan 19.11.2019

#ifndef OtaWrapper_H
#define OtaWrapper_H

#include <ArduinoOTA.h>

class OtaWrapper {
public:
    OtaWrapper(char *host, char *passwd) {
        ArduinoOTA.setHostname("4tingZ");
        ArduinoOTA.setPassword("123");
        startOTA();
    } 

    OtaWrapper(char *host, char *passwd, u_int port) {
        ArduinoOTA.setHostname(host);
        ArduinoOTA.setPassword(passwd);
        ArduinoOTA.setPort(port);
        startOTA();
    } 

    void startOTA() {
         Serial.println("Ota starting...");
         Serial.println("You hveave to be already connected on wifi netwerok"); 
            
            ArduinoOTA.onStart([]() {
                Serial.println("OTA Started");
            });

            ArduinoOTA.onEnd([]() {
                 Serial.println("\nOTA Ended");
            });

            ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
                Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
            });

            ArduinoOTA.onError([](ota_error_t error) {
                 Serial.printf("Error[%u]: ", error);
                  if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
                  else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
                  else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
                  else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
                  else if (error == OTA_END_ERROR) Serial.println("End Failed");
                  });
            ArduinoOTA.begin();
            Serial.println("Waiting for OTA");
    }

    void print() {
        Serial.println("OtaWrapper");
    }   

    void  handle() {
            ArduinoOTA.handle();
     }

};

extern OtaWrapper OTA;
#endif