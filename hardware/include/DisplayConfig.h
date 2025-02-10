#pragma once
#include <stdint.h>

// Common Font Configurations
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

// Common Display Settings
#define TFT_RGB_ORDER TFT_RGB

// Common SPI Settings
#define SPI_READ_FREQUENCY  20000000

// Pin Definitions Structure
struct DisplayPins {
    uint8_t CS;    // Chip Select
    uint8_t RST;   // Reset
    uint8_t DC;    // Data/Command
    uint8_t MOSI;  // SPI MOSI
    uint8_t SCLK;  // SPI Clock
    uint8_t BL;    // Backlight (optional)
};

// Display Configuration Structure
struct DisplayConfig {
    const char* setupInfo;
    uint16_t width;
    uint16_t height;
    uint32_t spiFreq;
    DisplayPins pins;
};
