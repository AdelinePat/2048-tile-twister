#ifndef TILEVIEW_HPP
#define TILEVIEW_HPP

#include "GameObject.hpp"
#include "Tile.hpp"
#include <memory>
#include <SDL3/SDL.h>

/**
 * TileView - Visual representation of a Tile
 * Inherits from GameObject for rendering, references a Tile for data
 */
class TileView : public GameObject {
public:
    TileView(SDL_Renderer* renderer, std::shared_ptr<Tile> tile,
             float x, float y, float size);

    void render() override;

    std::shared_ptr<Tile> getTile() const { return tile; }
    void setTile(std::shared_ptr<Tile> tile) { this->tile = tile; }

private:
    std::shared_ptr<Tile> tile;

    // Helper methods for rendering
    void getColorForValue(int value, SDL_Color& bgColor, SDL_Color& textColor);
    void renderRoundedRect(float x, float y, float w, float h, float radius);
    void renderText(const std::string& text, float x, float y, const SDL_Color& color);
};

#endif // TILEVIEW_HPP