// Jovan Svorcan 22.11.2019
// under MIT licence
#ifndef FILESYSMEMINFO_H
#define FILESYSMEMINFO_H

#include <FS.h>

class FileSysmemInfo {
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