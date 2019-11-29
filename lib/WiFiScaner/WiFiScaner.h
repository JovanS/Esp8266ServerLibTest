// Jovan Svorcan 22.11.2019
// under MIT licence
#ifndef WiFiScaner_h
#define WiFiScaner_h
 
#include <ESP8266WiFi.h> 

class WiFiScaner {
    public:
        static void scan() {
            Serial.println("\nNetwork scan");
            WiFi.scanDelete();
            int n = WiFi.scanNetworks(false, true);
            String ssid;
            uint8_t encryptionType;
            int32_t RSSI;
            uint8_t* BSSID;
            int32_t channel;
            bool isHidden;

            for (int i = 0; i < n; i++)
            {
                WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
                Serial.printf("%d: %s, Ch:%d (%ddBm) %s %s\n", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
            }
            Serial.println();
    }

        static String scanToString() {
            char data[50];
            String message("WiFi netwrok scan\n\n");
            int n = WiFi.scanNetworks(false, true);
            String ssid;
            uint8_t encryptionType;
            int32_t RSSI;
            uint8_t* BSSID;
            int32_t channel;
            bool isHidden;

            for (int i = 0; i < n; i++)
            {
                WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
                Serial.printf( "%d: %s, Ch:%d (%ddBm) %s %s\n", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
                sprintf(data,"%d: %s, Ch:%d (%ddBm) %s %s\n", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
                message+=data;
            }

            return message;
        }
};
#endif