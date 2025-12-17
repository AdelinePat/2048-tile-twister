
#include "Tile.hpp"
#include <vector>
#include <SDL3/SDL.h>

enum class Direction { UP, DOWN, LEFT, RIGHT};

class Grid {
private:
    Tile* tiles[4][4];

public:
    Grid();
    bool move(Direction dir);
    bool canMove() const;
    void mergeTiles(Direction dir);
    void addTile(Tile* tile);
    void addRandomTile();
    void render(SDL_Renderer* renderer) const;
};
