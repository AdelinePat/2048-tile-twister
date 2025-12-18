#pragma once
#include <SDL3/SDL.h>

#include <vector>

#include "gameObject.hpp"
#include "tileView.hpp"

class GridView : public GameObject {
  std::vector<TileView> tiles;

 public:
 
   /**
   * @brief Construct a new GridView object
   * @param x X position
   * @param y Y position
   * @param width Width of grid
   * @param height Height of grid
   * @param tiles Vector of TileView objects
   */
  GridView(int x, int y, int width, int height,
           const std::vector<TileView>& tiles);

  void setTiles(
      const std::vector<TileView>& newTiles);  ///< Set the tiles to render
  /**
   * @brief Render the grid and all tiles
   * @param renderer SDL renderer
   */
  void render(SDL_Renderer* renderer) override;
};
