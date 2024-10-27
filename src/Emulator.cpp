#include "Emulator.hpp"
#include "Consts.hpp"
#include <fstream>
#include <iostream>

void Emulator::InitEmulatorAudio() {
    m_audioPlayer.InitAudio();
}

void Emulator::LoadROMFromFile(const std::string& romPath) {
    
    std::ifstream romFile(romPath, std::ios::binary);

    if (!romFile.is_open())
        throw std::runtime_error("[ERROR] Unable to load the ROM !");

    romFile.seekg(0, std::ios::end);
    std::size_t romBufferSize = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    std::vector<uint8_t> romBuffer;

    romBuffer.reserve(romBufferSize);
    romFile.read(reinterpret_cast<char*>(romBuffer.data()), romBufferSize);
    romFile.close();

    // Load FONTSET before anything else.
    for (uint8_t i = 0; i < FONTSET_SIZE; i++) {
        m_memory.Write(i, FONTSET[i]);
    }

    for (std::size_t i = 0; i < romBufferSize; i++) {
        m_memory.Write(i + PROCESSOR_INTERNAL_PROGRAM_COUNTER_START, romBuffer[i]);
    }

    std::cout << "[INFO] ROM successfully loaded into memory !\n";
}

void Emulator::SetKey(uint8_t n, bool isDown) {
    m_executionUnit.SetKey(n, isDown);
}

void Emulator::UpdateExecutionUnitTimers() {
    m_executionUnit.UpdateTimers(m_audioPlayer);
}

void Emulator::ExecuteInstruction() {
    m_executionUnit.ExecuteInstruction(m_memory, m_renderTable);    
}

bool Emulator::IsPixelOn(uint8_t x, uint8_t y) {
    return m_renderTable.IsPixelOn(x, y);
}
