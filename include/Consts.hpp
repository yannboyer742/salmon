#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <cstdint>

static constexpr uint8_t CHIP8_SCREEN_WIDTH = 64;
static constexpr uint8_t CHIP8_SCREEN_HEIGHT = 32;
static constexpr uint8_t PIXEL_SCALE_FACTOR = 10;
static constexpr uint32_t WINDOW_WIDTH = CHIP8_SCREEN_WIDTH * PIXEL_SCALE_FACTOR;
static constexpr uint32_t WINDOW_HEIGHT = CHIP8_SCREEN_HEIGHT * PIXEL_SCALE_FACTOR;
static constexpr uint16_t CPU_CLOCK_DELAY = 1000;
static constexpr uint8_t TIMER_CLOCK_DIVISION = 9;
// Processor's PC starts at 0x200(512).
static constexpr uint16_t PROCESSOR_INTERNAL_PROGRAM_COUNTER_START = 0x200;

#endif
