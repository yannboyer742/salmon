#include "Audio.hpp"
#include <stdexcept>
#include <iostream>

Audio::~Audio() {
    if (m_beepSound)
        free(m_beepSound);
    Mix_CloseAudio();
}

void Audio::InitAudio() {
    if (Mix_OpenAudio(44100, AUDIO_S16LSB, MIX_DEFAULT_CHANNELS, 2048) < 0)
        throw std::runtime_error("[ERROR] Unable to initialize the audio backend !");

    m_beepSound = Mix_LoadWAV("beep_sound.wav");

    if (m_beepSound == nullptr)
        throw std::runtime_error("[ERROR] Unable to load the beep sound !");

    Mix_VolumeChunk(m_beepSound, MIX_MAX_VOLUME / 2);    
}

void Audio::PlayBeepSound() {
    int check = Mix_PlayChannel(-1, m_beepSound, 0);
    if (check < 0)
        std::cerr << "[WARNING] Can't play the beep sound !\n";
}
