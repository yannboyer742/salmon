#ifndef RENDER_TABLE_HPP
#define RENDER_TABLE_HPP

#include <cstdint>
#include <array>
#include "Consts.hpp"

enum class PixelState {
    On,
    Off,
};

class RenderTable {
    public:
        RenderTable();

        bool IsPixelOn(uint8_t x, uint8_t y);
        void ChangePixelStateTo(uint8_t x, uint8_t y, PixelState newState);
        void Clear();
    private:
        static constexpr uint16_t TOTAL_RENDER_TABLE_SIZE = CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT;
        std::array<PixelState, TOTAL_RENDER_TABLE_SIZE> m_renderTable;
};

#endif
