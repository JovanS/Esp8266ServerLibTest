// Jovan Svorcan 22.11.2019
// under MIT licence

#ifndef WEBSERVER_H
#define WEBSERVER_H 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <FS.h>
#include <ESP8266HTTPUpdateServer.h>
extern "C" {
#include "user_interface.h"
}

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer *server = new ESP8266WebServer;
char *Server_Pass;
char *Server_User;
bool auth=false; 
String message;

class WebServer { 
    public: 
            void handleClient() {  
                server->handleClient();
            }
            
            WebServer() { 
                delete server;
                server = new ESP8266WebServer(80);
                WebServer::postSetup();   
                server->begin();
                MDNS.addService("http", "tcp", 80); 
                MDNS.update();      
            }

            WebServer(int PORT) { 
                delete server;
                server = new ESP8266WebServer(PORT);
                WebServer::postSetup();   
                server->begin();
                MDNS.addService("http", "tcp", PORT);  
                MDNS.update();              
            }

            WebServer(char *USER, char *PASS){
                delete server;
                server = new ESP8266WebServer(80); 
                WebServer::postSetup(); 
                server->begin();
                auth=true;
                Server_User=USER; Server_Pass=PASS; 
                MDNS.addService("http", "tcp", 80); 
                MDNS.update();

            }

            WebServer(char *USER, char *PASS, int PORT){
                delete server;
                server = new ESP8266WebServer(PORT);
                WebServer::postSetup(); 
                server->begin();
                auth=true;
                Server_User=USER; Server_Pass=PASS;
                MDNS.addService("http", "tcp", PORT); 
                MDNS.update();
            } 

            void runFirmwareUpdater(bool activate_updater) {
                if(activate_updater) httpUpdater.setup(server); 
            }
    private:
        void postSetup(){ 
            SPIFFS.begin();   
            server->on("/test.html", std::bind(&WebServer::handletest, this));  
            server->on("/podaci.js", std::bind(&WebServer::handlePodaci, this));  
            server->onNotFound(std::bind(&WebServer::handleNotFound, this)); 
        }

        void handleNotFound() {
            if(! WebServer::handleFileRead(server->uri())) {
                Serial.println("404: Not Found");
                server->send(404, "text/plain", "404: Not Found "+server->uri());
            }
            
        }

        String getContentType(String filename) { // convert the file extension to the MIME type
            if (filename.endsWith(".html")) return "text/html";
            else if (filename.endsWith(".css")) return "text/css";
            else if (filename.endsWith(".js")) return "application/javascript";
            else if (filename.endsWith(".ico")) return "image/x-icon";
            return "text/plain";
            }

        bool handleFileRead(String path) { // send the right file to the client (if it exists)
            Serial.println("handleFileRead: " + path);

              if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
   
            // Creting file before servin it.
            // if(path=="/podaci.js") {     
            //     String data = "var milis="+String(millis(), DEC)+";"; 
            //     Serial.println(data);
            //     File file = SPIFFS.open("/podaci.js", "w");
            //     file.println(data); 
            //     file.close();
            // }
  
            String contentType = getContentType(path);            // Get the MIME type
                if (SPIFFS.exists(path)) {                            // If the file exists
                File file = SPIFFS.open(path, "r");                 // Open it
                size_t sent = server->streamFile(file, contentType); // And send it to the client
                file.close();                                       // Then close the file again
                return true;
            }
            Serial.println("\tFile Not Found");
            return false;                                         // If the file doesn't exist, return false
    }

        void handletest () {
            message="<!DOCTYPE html>";
            message=+"Radi is server.on callbacka";
            server->send(200, "text/html", message );
        }            

        void handlePodaci () {
            message = "var milis="+String(millis(), DEC)+";"; 
            Serial.println("\nPoslato kao podaci: "+message);
            server->send(200, "application/javascript", message );
        }
};

extern WebServer WServ;
#endif