#include "gridView.hpp"

#include <SDL3/SDL.h>

GridView::GridView(int x, int y, int width, int height,
                   const std::vector<TileView>& tiles)
    : GameObject(x, y, width, height), tiles(tiles) {}

void GridView::setTiles(const std::vector<TileView>& newTiles) {
  this->tiles = newTiles;
}

void GridView::render(SDL_Renderer* renderer) {
  // Draw grid background
  SDL_FRect rect = {static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(width), static_cast<float>(height)};
  SDL_SetRenderDrawColor(renderer, 180, 170, 160, 255);
  SDL_RenderFillRect(renderer, &rect);
  // Draw all tiles
  for (TileView& tile : tiles) {
    tile.render(renderer);
  }
}
