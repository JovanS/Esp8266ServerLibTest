#ifndef WEBSERVER_H
#define WEBSERVER_H 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <FS.h>
extern "C" {
#include "user_interface.h"
}

ESP8266WebServer *servera = new ESP8266WebServer(80);
ESP8266WebServer  server;
char *Server_Pass;
char *Server_User;
bool auth=false; 

class WebServer { 
    public: 
            void handleClient() {  
                server.handleClient();
            }
            
            WebServer() {
                // ESP8266WebServer  servera(80); 
                WebServer::postSetup(); 
                MDNS.addService("http", "tcp", 80); 
                // MDNS.update();      
            }

            WebServer(int PORT) { 
                WebServer::postSetup(); 
                // *server=new &ESP8266WebServer(80);
                delete servera;
                servera = new ESP8266WebServer(90);
                server.begin();
                MDNS.addService("http", "tcp", PORT);  
                // MDNS.update();              
            }

            WebServer(char *USER, char *PASS){
                //  ESP8266WebServer  servertmp(80); 
                WebServer::postSetup(); 
                server.begin();
                auth=true;
                Server_User=USER; Server_Pass=PASS; 
                MDNS.addService("http", "tcp", 80); 
                // MDNS.update();

            }

            WebServer(char *USER, char *PASS, int PORT){
                // ESP8266WebServer  server(PORT);
                WebServer::postSetup(); 
                server.begin();
                auth=true;
                Server_User=USER; Server_Pass=PASS;
                MDNS.addService("http", "tcp", PORT); 
                // MDNS.update();
            } 
    private:
        void postSetup(){ 
            SPIFFS.begin();   
            server.onNotFound(std::bind(&WebServer::handleNotFound, this)); 
            // Serial.println("seting up callbacks");
            // if (! WebServer::handleFileRead(server.uri())) {   
            //     server.onNotFound(std::bind(&WebServer::handleNotFound, this));      
            // }
            // WebServer::handleFileRead(server.uri());
        }

        void handleNotFound() {
            if(! WebServer::handleFileRead(server.uri())) {
                Serial.println("404: Not Found2233");
                server.send(404, "text/plain", "404: Not Found2233");
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
  
            // OVO SAM DODAO DA PRESRETNEM STRANU I KREIRAM JE IZ KODA
            // Joca
            if(path=="/Test.html") {     
                handletest ();
                return true;
            }

   // OVO SAM DODAO DA U MOMENTU KAD ZATRAZI PODACI.JS PROMENIM SADRZAJ FAJLSA
    // Joca

            if(path=="/podaci.js") {     
                String data = "var milis="+String(millis(), DEC)+";"; 
                Serial.println(data);
                File file = SPIFFS.open("/podaci.js", "w");
                file.println(data); 
                file.close();
            }
  
            String contentType = getContentType(path);            // Get the MIME type
                if (SPIFFS.exists(path)) {                            // If the file exists
                File file = SPIFFS.open(path, "r");                 // Open it
                size_t sent = server.streamFile(file, contentType); // And send it to the client
                file.close();                                       // Then close the file again
                return true;
            }
            Serial.println("\tFile Not Found");
            return false;                                         // If the file doesn't exist, return false
    }

        void handletest () {
            server.send(200, "text/plan", "RADIII" );
        }            

};

extern WebServer WServ;
#endif