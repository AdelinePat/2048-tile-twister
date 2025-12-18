
#include <SDL3/SDL.h>

#include <vector>

#include "tile.hpp"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Grid {
 private:
  Tile* tiles[4][4];

 public:
  Grid();
  bool move(Direction dir);
  bool isCellEmpty() const;
  bool canMerge() const;
  bool canMove() const;
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  void mergeTiles(Direction dir);
  void addTile(Tile* tile);
  void addRandomTile();
  Tile* getTile(int i, int j) const { return tiles[i][j]; }
  // void render(SDL_Renderer* renderer) const; // rendering is now handled by
  // GridView
};
