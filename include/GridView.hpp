#ifndef GRIDVIEW_HPP
#define GRIDVIEW_HPP

#include "GameObject.hpp"
#include "Grid.hpp"
#include "TileView.hpp"
#include <vector>
#include <memory>

/**
 * GridView - Visual representation of the game grid
 * Manages rendering of all tiles and the grid background
 */
class GridView : public GameObject {
public:
    GridView(SDL_Renderer* renderer, std::shared_ptr<Grid> grid,
             float x, float y, float size);

    void render() override;
    void updateTileViews();  // Sync tile views with grid state

private:
    std::shared_ptr<Grid> grid;
    std::vector<std::vector<std::shared_ptr<TileView>>> tileViews;

    float padding;    // Space between tiles
    float tileSize;   // Size of each tile

    void initializeTileViews();
    void renderBackground();
};

#endif // GRIDVIEW_HPP