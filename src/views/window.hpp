#pragma once
#include <SDL3/SDL.h>

#include "../core/game.hpp"
#include "gridView.hpp"

   /**
   * @class Window
   * @brief Main application window and event/render loop for 2048 game.
   */
class Window {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Game game;
  GridView* gridView;
  bool running;

 public:
  Window();
  ~Window();
  void init();            ///< Initialize SDL, SDL_ttf, and game state
  void render();          ///< Render the current game state
  void handleEvents();    ///< Handle SDL events (keyboard, quit, etc.)
  void loop();            ///< Main application/game loop
  void updateGridView();  ///< Update the GridView from the current Grid state
};