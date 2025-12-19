#pragma once
#include <memory>
#include <vector>

#include "tile.hpp"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Grid {
 private:
  std::unique_ptr<Tile> tiles[4][4];

  // Sliding operations
  void slideTiles(Direction dir, bool& moved);
  void slideLeft(bool& moved);
  void slideRight(bool& moved);
  void slideUp(bool& moved);
  void slideDown(bool& moved);

  // Merging operations
  void mergeLeft();
  void mergeRight();
  void mergeUp();
  void mergeDown();

  // Helper methods
  void resetAllMergeStates();
  std::vector<std::pair<int, int>> getEmptyCells() const;

 public:
  Grid() = default;
  ~Grid() = default;

  // Smart pointers handle copying/moving automatically
  Grid(Grid&&) = default; // transfert ownership from new grid into current grid
  Grid& operator=(Grid&&) = default; // pretty much the same  grid2 = std::move(grid1) OK

  // Disable copying (or implement deep copy if needed)
  Grid(const Grid&) = delete; // won't allow grid2 = grid1
  Grid& operator=(const Grid&) = delete;

  // Game operations
  bool move(Direction dir);
  void mergeTiles(Direction dir);

  // Tile management
  void addTile(Tile* tile);  // Takes ownership
  void addRandomTile();
  Tile* getTile(int i, int j) const { return tiles[i][j].get(); }

  // Game state queries
  bool hasEmptyCell() const;
  bool canMerge() const;
  bool canMove() const;
  bool hasValue(int targetValue) const;

  // Utility
  void clear();
};