#include <SDL3/SDL.h>

#include <iostream>
#include "Window.hpp"

int main() {
    Window window;
    window.init();
    window.loop();
    
    // // INIT SDL
    // if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //     std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
    //     return -1;
    // }

    // CREATE WINDOW
    // SDL_Window* window = SDL_CreateWindow(
    //     "2048 - Tile Twister",               
    //     640,                        
    //     480,                        
    //     SDL_WINDOW_RESIZABLE        // options
    // );

    // if (!window) {
    //     std::cerr << "Erreur création fenêtre: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return -1;
    // }

 

    //CREATE RENDERER
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    // if (!renderer) {
    //     std::cerr << "Erreur création renderer: " << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return -1;
    // }

    // Grid grid;
    // grid.addRandomTile();
    // grid.addRandomTile();

    // bool running = true;
    // SDL_Event event;
    // while (running) {
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_EVENT_QUIT) {
    //             running = false;
    //         }
    //     }

       
     
        // SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        // SDL_RenderClear(renderer);

        // grid.render(renderer);

    
        // SDL_FRect tile1 { 50, 50, 100, 100 };
        // SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
        // SDL_RenderFillRect(renderer, &tile1);

       
        // SDL_FRect tile2 { 200, 200, 100, 100 };
        // SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        // SDL_RenderFillRect(renderer, &tile2);

           //CHANGE BACKGROUND COLOR
    // SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);


    // SDL_RenderPresent(renderer);
    // }

 

    // DELAY
    // SDL_Delay(16);

    // DESTROY WINDOW
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    return 0;
}
