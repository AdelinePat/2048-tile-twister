#include "Window.hpp"
#include <iostream> 

Window::Window() : window(nullptr), renderer(nullptr), running(true) {}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("2048 - Tile Twister", 640, 480, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, nullptr);
    game.addRandomTile();
    game.addRandomTile();

}

void Window::render() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    SDL_RenderClear(renderer);

    game.getGrid().render(renderer);

SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Keycode key = event.key.key;  
            switch (key) {
            case SDLK_LEFT:
                game.move(Direction::LEFT);
                game.addRandomTile();
                break;
            case SDLK_RIGHT:
                game.move(Direction::RIGHT);
                game.addRandomTile();
                break;
            case SDLK_UP:
                game.move(Direction::UP);
                game.addRandomTile();
                break;
            case SDLK_DOWN:
                game.move(Direction::DOWN);
                game.addRandomTile();
                break;
            }
        }
    }
}



void Window::loop() {
     while (running) {
        handleEvents();
         render(); 
        if (!game.isGameOver()) {
             //TODO : window game over to implant
        }

        SDL_Delay(16);
    }
}




