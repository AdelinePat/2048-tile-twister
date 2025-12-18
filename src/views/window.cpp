#include "window.hpp"

#include <iostream>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>

#include "gridView.hpp"
#include "tileView.hpp"

Window::Window()
  : window(nullptr), renderer(nullptr), running(true), gridView(nullptr) {}

Window::~Window() {
  if (gridView) delete gridView;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

void Window::init() {
  SDL_Init(SDL_INIT_VIDEO);
  if (TTF_Init() < 0) {
    std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
  }
  window =
      SDL_CreateWindow("2048 - Tile Twister", 640, 480, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, nullptr);
  game.addRandomTile();
  game.addRandomTile();
  updateGridView();
}

void Window::renderMessage(const std::string& message) {
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf", 48);
    if (!font) {
        std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(
        font, message.c_str(), message.length(), textColor);
    
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            int winW, winH;
            SDL_GetRenderOutputSize(renderer, &winW, &winH);
            
            int textW = textSurface->w;
            int textH = textSurface->h;
            
              // BACKRGROUND BLURING
            SDL_FRect bgRect = {
                static_cast<float>((winW - textW - 40) / 2),
                static_cast<float>((winH - textH - 40) / 2),
                static_cast<float>(textW + 40),
                static_cast<float>(textH + 40)
            };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
            SDL_RenderFillRect(renderer, &bgRect);
            
            //Position of the text
            SDL_FRect dstRect = {
                static_cast<float>((winW - textW) / 2),
                static_cast<float>((winH - textH) / 2),
                static_cast<float>(textW),
                static_cast<float>(textH)
            };
            SDL_RenderTexture(renderer, textTexture, nullptr, &dstRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
    }
    TTF_CloseFont(font);
}

void Window::render() {
  SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
  SDL_RenderClear(renderer);
  
  if (gridView) gridView->render(renderer);
  
  // Message of loose or victory
  if (game.hasWon()) {
      renderMessage("Tu as gagne !");
  } else if (game.isGameOver()) {
      renderMessage("Tu as perdu !");
  }
  
  SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
  if (game.hasWon() || game.isGameOver()) return;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_LEFT:  game.move(Direction::LEFT); break;
                case SDLK_RIGHT: game.move(Direction::RIGHT); break;
                case SDLK_UP:    game.move(Direction::UP);    break;
                case SDLK_DOWN:  game.move(Direction::DOWN);  break;
            }
            updateGridView();
        }
    }
}

void Window::loop() {
  while (running) {
    handleEvents();
    render();
    SDL_Delay(16);
  }
}

void Window::updateGridView() {
  if (gridView) delete gridView;
  
  int cellSize = 100;
  int gridW = 4 * cellSize;
  int gridH = 4 * cellSize;
  int winW = 640, winH = 480;
  if (renderer) SDL_GetRenderOutputSize(renderer, &winW, &winH);
  int offsetX = (winW - gridW) / 2;
  int offsetY = (winH - gridH) / 2;
  
  std::vector<TileView> tileViews;
  Grid& grid = game.getGrid();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      Tile* tile = grid.getTile(i, j);
      if (tile) {
        int val = tile->getValue();
        tileViews.emplace_back(offsetX + j * cellSize, offsetY + i * cellSize,
                               cellSize, cellSize, val);
      }
    }
  }
  gridView = new GridView(offsetX, offsetY, gridW, gridH, tileViews);
}