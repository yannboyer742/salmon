#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "Emulator.hpp"
#include <chrono>
#include <thread>
#include "Consts.hpp"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "[ERROR] Usage : ./salmon my_game.rom/my_game.ch8\n";
        std::cerr << "[ERROR] No ROM provided !\n";
        return EXIT_FAILURE;
    }

    std::string romPath = std::string(argv[1]);

    Emulator chip8Emulator;

    try {
        chip8Emulator.InitEmulatorAudio();
        chip8Emulator.LoadROMFromFile(romPath);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Chip8VM by Yann BOYER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "[ERROR] Unable to initialize the window !\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == nullptr) {
        std::cerr << "[ERROR] Unable to initialize the renderer !\n";
        return EXIT_FAILURE;
    }

    bool isRunning = true;
    uint8_t divCycles = 0;

    SDL_RenderClear(renderer); // Just to be sure...

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "[INFO] Exiting...\n";
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    break;
                case SDL_KEYUP:
                    break;
                default: break;
            }
        }

        chip8Emulator.ExecuteInstruction();
        divCycles++;

        // Draw on screen.
        for (uint8_t y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
            for (uint8_t x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
                SDL_Rect pixel = { x * PIXEL_SCALE_FACTOR, y * PIXEL_SCALE_FACTOR, PIXEL_SCALE_FACTOR, PIXEL_SCALE_FACTOR };
                if (chip8Emulator.IsPixelOn(x, y))
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &pixel);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        if (divCycles == TIMER_CLOCK_DIVISION) {
            chip8Emulator.UpdateExecutionUnitTimers();
            divCycles = 0;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(CPU_CLOCK_DELAY));
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
