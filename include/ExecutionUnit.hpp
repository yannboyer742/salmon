#ifndef EXECUTION_UNIT_HPP
#define EXECUTION_UNIT_HPP

#include <cstdint>
#include <array>
#include <vector>
#include "Audio.hpp"
#include "RenderTable.hpp"
#include "Memory.hpp"

enum class KeyState {
    Pressed,
    NotPressed,
};

class ExecutionUnit {
    public:
        ExecutionUnit();

        void UpdateTimers(Audio& audioPlayer);  
        void SetKey(uint8_t n, bool isDown);
        void ExecuteInstruction(Memory& memory, RenderTable& renderTable);
    private:
        uint16_t FetchNextInstruction(Memory& memory);

        static constexpr uint8_t REGISTERS_COUNT = 16;
        static constexpr uint8_t KEYS_COUNT = 16;

        std::array<uint8_t, REGISTERS_COUNT> m_registers;
        std::array<KeyState, KEYS_COUNT> m_keys;
        std::vector<uint16_t> m_stack;

        uint16_t m_indexRegister;
        uint8_t m_delayTimer;
        uint8_t m_soundTimer;
        uint16_t m_programCounter;
};

#endif
