#pragma once
#include <SDL3/SDL.h>

#include <iostream>
#include <string>

#include "gameObject.hpp"

class TileView : public GameObject {
  int value;

 public:
 
    /**
   * @brief Construct a new TileView object
   * @param x X position
   * @param y Y position
   * @param width Width of tile
   * @param height Height of tile
   * @param value Value to display
   */
  TileView(int x, int y, int width, int height, int value);
  void setValue(int v); 
  int getValue() const;
  /**
   * @brief Render the tile and its value
   * @param renderer SDL renderer
   */
  void render(SDL_Renderer* renderer) override;
};
