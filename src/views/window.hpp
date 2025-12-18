#pragma once
#include <SDL3/SDL.h>

#include "../core/game.hpp"
#include "gridView.hpp"

class Window {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Game game;
  GridView* gridView;
  bool running;

  void renderMessage(const std::string& message); 

 public:
  Window();
  ~Window();
  void init();
  void render();
  void handleEvents();
  void loop();
  void updateGridView();
};