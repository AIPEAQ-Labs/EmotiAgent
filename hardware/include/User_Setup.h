// Main display configuration entry point
#pragma once

// Choose your display type by uncommenting one of these:
#include "ST7789Config.h"
// #include "ST7735Config.h"

// Common display settings are now in DisplayConfig.h
#include "DisplayConfig.h"

// Additional settings specific to this setup
#define SPI_TOUCH_FREQUENCY   2500000
