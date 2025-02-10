#ifndef SERIALNUMBER_H
#define SERIALNUMBER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <WiFi.h>

class SerialNumber {
public:
    static std::string serialNumber;
    // Convert MAC address to Apple serial number
    static std::string macToSerial(const std::string& macAddress) {
        // Remove any separators from MAC address
        std::string cleanMac = removeSeparators(macAddress);
        
        // Validate MAC address length
        if (cleanMac.length() != 12) {
            throw std::invalid_argument("Invalid MAC address format");
        }
        
        // Extract last 6 digits of MAC
        std::string lastSixDigits = cleanMac.substr(6);
        
        // Convert to integer
        unsigned long long macNum = std::stoull(lastSixDigits, nullptr, 16);
        
        // Generate serial number
        return generateSerialNumber(macNum);
    }


    static std::string getSerialNumber() {
        if (serialNumber == "") {
            const char* mac = WiFi.macAddress().c_str();
            Serial.println(mac);
            serialNumber = macToSerial(mac);
        }

        return serialNumber;
    }

private:
    // Remove separators like : or - from MAC address
    static std::string removeSeparators(const std::string& macAddress) {
        std::string cleaned;
        for (char c : macAddress) {
            if (std::isxdigit(c)) {
                cleaned += c;
            }
        }
        return cleaned;
    }

    // Generate Apple-style serial number
    static std::string generateSerialNumber(unsigned long long macNum) {
        // Apple serial number format typically starts with a letter
        const std::string prefix = "I02";
        
        // Use the last 6 digits of MAC to generate a unique identifier
        unsigned long long serialNum = macNum % 1000000;
        
        // Convert to base 36 encoding for more compact representation
        std::string encoded = base36Encode(serialNum);
        
        // Pad or truncate to ensure consistent length
        while (encoded.length() < 8) {
            encoded = "0" + encoded;
        }
        
        if (encoded.length() > 8) {
            encoded = encoded.substr(encoded.length() - 8);
        }
        
        return prefix + encoded;
    }

    // Convert number to base 36 (0-9 and A-Z)
    static std::string base36Encode(unsigned long long num) {
        const std::string base36Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string result;
        
        while (num > 0) {
            result = base36Chars[num % 36] + result;
            num /= 36;
        }
        
        return result;
    }
};

std::string SerialNumber::serialNumber;
#endif // SERIALNUMBER_H
