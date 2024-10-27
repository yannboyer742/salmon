#include "RenderTable.hpp"
#include "Consts.hpp"
#include <iostream>

RenderTable::RenderTable() {
   m_renderTable.fill(PixelState::Off);
}

bool RenderTable::IsPixelOn(uint8_t x, uint8_t y) {
   if (x > CHIP8_SCREEN_WIDTH || y > CHIP8_SCREEN_HEIGHT) {
      std::cerr << "[WARNING] Invalid coordinates -> X : " << unsigned(x) << " Y : " << unsigned(y) << "\n";
      return false;
   }

   return m_renderTable[y * CHIP8_SCREEN_WIDTH + x] == PixelState::On;
}

void RenderTable::ChangePixelStateTo(uint8_t x, uint8_t y, PixelState newState) {
   if (x > CHIP8_SCREEN_WIDTH || y > CHIP8_SCREEN_HEIGHT) {
      std::cerr << "[WARNING] Invalid coordinates -> X : " << unsigned(x) << " Y : " << unsigned(y) << "\n";
      return;
   }

   m_renderTable[y * CHIP8_SCREEN_WIDTH + x] = newState;
}

void RenderTable::Clear() {
   for (uint8_t y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
      for (uint8_t x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
         m_renderTable[y * CHIP8_SCREEN_WIDTH + x] = PixelState::Off;
      }
   }
}
