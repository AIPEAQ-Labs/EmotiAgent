#pragma once

#include <SPIFFS.h>

class SPIFFSHandler {
public:
    // Initialize SPIFFS
    static bool begin() {
        return SPIFFS.begin(true);  // Format on failure
    }

    // File operations
    static void listDir(const char* dirname, uint8_t levels);
    static void readFile(const char* path);
    static void writeFile(const char* path, const char* message);
    static void appendFile(const char* path, const char* message);
    static void renameFile(const char* path1, const char* path2);
    static void deleteFile(const char* path);
    static void testFileIO(const char* path);

private:
    // Make constructor private to prevent instantiation
    SPIFFSHandler() {}
};

