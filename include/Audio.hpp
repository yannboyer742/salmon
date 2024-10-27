#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL2/SDL_mixer.h>

class Audio {
    public:
        Audio() = default;
        ~Audio();

        void InitAudio();
        void PlayBeepSound();  
    private:
        Mix_Chunk* m_beepSound;
};

#endif
