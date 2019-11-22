// Jovan Svorcan 22.11.2019
// under MIT licence
#ifndef FILESYSREMINFO_H
#define FILESYSREMINFO_H

#include <FS.h>

class FileSysremInfo {
    public:
        static void info() {
            SPIFFS.begin();
            Dir dir = SPIFFS.openDir("/");
            Serial.println("Files in flash memory:");
            while (dir.next()) 
            Serial.printf("FS File: %s\n", dir.fileName().c_str());
        }

};
#endif