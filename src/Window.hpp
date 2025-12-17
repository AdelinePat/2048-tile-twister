#pragma once
#include "Game.hpp"
#include <SDL3/SDL.h>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game game;
    bool running;

public:
    Window();
    ~Window();
    void init();
    void render();
    void handleEvents();
    void loop();
};