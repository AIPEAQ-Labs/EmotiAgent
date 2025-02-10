#pragma once

#include <ESP32OTAPull.h>
#include <SerialNumber.h>
class OTA : public ESP32OTAPull
{
private:
    unsigned long lastCheck = 0;
    const unsigned long CHECK_INTERVAL = 1 * 60 * 1000;

public:
    static void callback(int offset, int totallength) {
        Serial.printf("Updating %d of %d (%02d%%)...\n", offset, totallength, 100 * offset / totallength);
    #if defined(LED_BUILTIN) // flicker LED on update
        static int status = LOW;
        status = status == LOW && offset < totallength ? HIGH : LOW;
        digitalWrite(LED_BUILTIN, status);
    #endif
    }

    const char *errtext(int code) {
        switch(code)
        {
            case ESP32OTAPull::UPDATE_AVAILABLE:
                return "An update is available but wasn't installed";
            case ESP32OTAPull::NO_UPDATE_PROFILE_FOUND:
                return "No profile matches";
            case ESP32OTAPull::NO_UPDATE_AVAILABLE:
                return "Profile matched, but update not applicable";
            case ESP32OTAPull::UPDATE_OK:
                return "An update was done, but no reboot";
            case ESP32OTAPull::HTTP_FAILED:
                return "HTTP GET failure";
            case ESP32OTAPull::WRITE_ERROR:
                return "Write error";
            case ESP32OTAPull::JSON_PROBLEM:
                return "Invalid JSON";
            case ESP32OTAPull::OTA_UPDATE_FAIL:
                return "Update fail (no OTA partition?)";
            default:
                if (code > 0)
                    return "Unexpected HTTP response code";
                break;
        }
        return "Unknown error";
    }

    void setup() {
        this->SetCallback(callback);
    }

    void loop(const char* jsonUrl, const char *currentVersion) {
        if (WiFi.status() == WL_CONNECTED && millis() - lastCheck > CHECK_INTERVAL) {
            Serial.println("Checking for OTA update");
            int ret = this->CheckForOTAUpdate(jsonUrl, currentVersion, SerialNumber::getSerialNumber().c_str());
            lastCheck = millis();
        }
    }
};
