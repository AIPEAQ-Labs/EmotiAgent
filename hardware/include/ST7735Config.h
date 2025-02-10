#pragma once
#include "DisplayConfig.h"

// ST7735 Display Configuration
#define ST7735_DRIVER

// Standard ST7735 Configuration (128x160)
const DisplayConfig ST7735_CONFIG_STANDARD = {
    .setupInfo = "ST7735_128x160",
    .width = 128,
    .height = 160,
    .spiFreq = 27000000,
    .pins = {
        .CS = 39,
        .RST = 6,
        .DC = 15,
        .MOSI = 35,
        .SCLK = 36,
        .BL = 0
    }
};

// Backup ST7735 Configuration (160x128)
const DisplayConfig ST7735_CONFIG_BACKUP = {
    .setupInfo = "ST7735_160x128",
    .width = 160,
    .height = 128,
    .spiFreq = 20000000,
    .pins = {
        .CS = 39,
        .RST = 6,
        .DC = 15,
        .MOSI = 35,
        .SCLK = 36,
        .BL = 5
    }
};

// Select which configuration to use (change this to switch between configurations)
#define USE_STANDARD_CONFIG

#ifdef USE_STANDARD_CONFIG
    #define ACTIVE_CONFIG ST7735_CONFIG_STANDARD
#else
    #define ACTIVE_CONFIG ST7735_CONFIG_BACKUP
#endif

// Macro definitions for backward compatibility
#define TFT_WIDTH  ACTIVE_CONFIG.width
#define TFT_HEIGHT ACTIVE_CONFIG.height
#define TFT_CS     ACTIVE_CONFIG.pins.CS
#define TFT_RST    ACTIVE_CONFIG.pins.RST
#define TFT_DC     ACTIVE_CONFIG.pins.DC
#define TFT_MOSI   ACTIVE_CONFIG.pins.MOSI
#define TFT_SCLK   ACTIVE_CONFIG.pins.SCLK
#define TFT_BL     ACTIVE_CONFIG.pins.BL
#define SPI_FREQUENCY ACTIVE_CONFIG.spiFreq
