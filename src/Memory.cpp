#include "Memory.hpp"
#include <iostream>

Memory::Memory() {
    m_memory.fill(0x0);
}

void Memory::Write(uint16_t addr, uint8_t data) {
    if (addr > TOTAL_MEMORY_SIZE - 1) {
        std::cerr << "[WARNING] Memory WRITE command is out of range !\n";
        return;
    }

    m_memory[addr] = data;
}

uint8_t Memory::Read(uint16_t addr) {
    if (addr > TOTAL_MEMORY_SIZE - 1) {
        std::cerr << "[WARNING] Memory READ command is out of range !\n";
        return 0x0;
    }

    return m_memory[addr];
}
