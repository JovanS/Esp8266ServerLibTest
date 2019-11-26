#ifndef MAIN_H
#define MAIN_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h> 
#include <WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h> 
#include <filesysremInfo.h>
#include <WiFiConnect.h>
#include <WiFiScaner.h> 

void wifiScan(); 
void wifiConnect();
void filesystemInfo();

WebServer wserv;  
#endif