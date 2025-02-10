#pragma once
#include "DisplayConfig.h"

// ST7789 Display Configuration
#define ST7789_DRIVER

const DisplayConfig ST7789_CONFIG = {
    .setupInfo = "ST7789_240x280",
    .width = 240,
    .height = 280,
    .spiFreq = 27000000,
    .pins = {
        .CS = 39,
        .RST = 6,
        .DC = 16,
        .MOSI = 11,
        .SCLK = 12,
        .BL = 48
    }
};

// Macro definitions for backward compatibility
#define TFT_WIDTH  ST7789_CONFIG.width
#define TFT_HEIGHT ST7789_CONFIG.height
#define TFT_CS     ST7789_CONFIG.pins.CS
#define TFT_RST    ST7789_CONFIG.pins.RST
#define TFT_DC     ST7789_CONFIG.pins.DC
#define TFT_MOSI   ST7789_CONFIG.pins.MOSI
#define TFT_SCLK   ST7789_CONFIG.pins.SCLK
#define TFT_BL     ST7789_CONFIG.pins.BL
#define SPI_FREQUENCY ST7789_CONFIG.spiFreq
