
// #include <SDL3/SDL.h>

#include <vector>

#include "tile.hpp"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Grid {
 private:
  Tile* tiles[4][4];
  void slideTiles(Direction dir, bool& moved);
  void slideLeft(bool& moved);
  void slideRight(bool& moved);
  void slideUp(bool& moved);
  void slideDown(bool& moved);
  void mergeLeft();
  void mergeRight();
  void mergeUp();
  void mergeDown();

 public:
  Grid();
  bool move(Direction dir);
  bool isCellEmpty() const;
  bool canMerge() const;
  bool canMove() const;
  void addTile(Tile* tile);
  void addRandomTile();
  Tile* getTile(int i, int j) const { return tiles[i][j]; }
  void mergeTiles(Direction dir);
};
