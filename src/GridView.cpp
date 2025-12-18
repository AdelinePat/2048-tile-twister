#include "GridView.hpp"

GridView::GridView(SDL_Renderer* renderer, std::shared_ptr<Grid> grid, 
                   float x, float y, float size)
    : GameObject(renderer, x, y, size, size), grid(grid) {
    
    padding = 10.0f;
    tileSize = (size - padding * (Grid::SIZE + 1)) / Grid::SIZE;
    
    initializeTileViews();
}

void GridView::initializeTileViews() {
    tileViews.resize(Grid::SIZE);
    
    for (int row = 0; row < Grid::SIZE; ++row) {
        tileViews[row].resize(Grid::SIZE);
        for (int col = 0; col < Grid::SIZE; ++col) {
            float tileX = x + padding + col * (tileSize + padding);
            float tileY = y + padding + row * (tileSize + padding);
            
            auto tile = grid->getTile(row, col);
            tileViews[row][col] = std::make_shared<TileView>(
                renderer, tile, tileX, tileY, tileSize
            );
        }
    }
}

void GridView::updateTileViews() {
    // Sync each TileView with its corresponding Tile in the Grid
    for (int row = 0; row < Grid::SIZE; ++row) {
        for (int col = 0; col < Grid::SIZE; ++col) {
            tileViews[row][col]->setTile(grid->getTile(row, col));
        }
    }
}

void GridView::renderBackground() {
    // Draw grid background
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);  // Grid background color
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void GridView::render() {
    renderBackground();
    
    // Render all tiles
    for (int row = 0; row < Grid::SIZE; ++row) {
        for (int col = 0; col < Grid::SIZE; ++col) {
            tileViews[row][col]->render();
        }
    }
}