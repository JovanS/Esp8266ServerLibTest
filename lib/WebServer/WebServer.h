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
#include <WiFiScaner.h>

ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer *server; 
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
                server = new ESP8266WebServer(80);
                WebServer::postSetup();   
                server->begin();
                MDNS.addService("http", "tcp", 80); 
                MDNS.update();      
            }

            WebServer(int PORT) {  
                server = new ESP8266WebServer(PORT);
                WebServer::postSetup();   
                server->begin();
                MDNS.addService("http", "tcp", PORT);  
                MDNS.update();              
            }

            WebServer(char *USER, char *PASS){ 
                server = new ESP8266WebServer(80); 
                WebServer::postSetup(); 
                server->begin();
                auth=true;
                Server_User=USER; Server_Pass=PASS; 
                MDNS.addService("http", "tcp", 80); 
                MDNS.update();

            }

            WebServer(char *USER, char *PASS, int PORT){ 
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
            server->on("/scan.html", std::bind(&WebServer::handleScan, this)); 
            server->on("/podesi.html", std::bind(& WebServer::handlePodesi, this));
            server->onNotFound(std::bind(&WebServer::handleNotFound, this)); 
        }

        void handleNotFound() {
            if(! WebServer::handleFileRead(server->uri())) {
                Serial.println("404: Not Found");
                server->send(404, "text/plain", "404: Not Found "+server->uri());
            }
            
        }

        String getContentType(String filename) { // convert the file extension to the MIME type
            if(filename.endsWith(".html")) return "text/html"; 
            else if(filename.endsWith(".css")) return "text/css";
            else if(filename.endsWith(".js"))  return "application/javascript";
            else if(filename.endsWith(".png")) return "image/png";
            else if(filename.endsWith(".gif")) return "image/gif";
            else if(filename.endsWith(".jpg")) return "image/jpeg";
            else if(filename.endsWith(".ico")) return "image/x-icon";
            else if(filename.endsWith(".xml")) return "text/xml";
            else if(filename.endsWith(".pdf")) return "application/pdf";
            else if(filename.endsWith(".zip")) return "application/zip";
            return "text/plain"; 
            }

        bool handleFileRead(String path) { // send the right file to the client (if it exists)
            Serial.println("handleFileRead: " + path);

              if (path.endsWith("/")) path += "index.html";     
  
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

        void handleScan () { 
            server->send(200, "text/plain", WiFiScaner::scanToString() );
        }

        void handlePodesi() { 
            String message("URI:");
                message += server->uri();
                message += "\nMethod: ";
                message += (server->method() == HTTP_GET)?"GET":"POST";
                message += "\nArguments: ";
                message += server->args();
                message += "\n";
                for (uint8_t i=0; i<server->args(); i++){
                
                message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
                }
                server->send(200, "text/html", "OK ZA SAD :)" ); 

            Serial.print("Received pareameters: ");
            Serial.println(+server->args());
            for(int i=0; i<server->args(); i++) {     
            String tester(server->argName(i));
            String argument(server->arg(i));
            Serial.print(tester+" = ");
            Serial.println(argument);
            }
        }
};

extern WebServer WServ;
#endif