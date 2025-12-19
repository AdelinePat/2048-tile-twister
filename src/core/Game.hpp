#pragma once
#include "grid.hpp"

class Game {
 private:
  Grid grid;
  // int score;
  // bool won;

 public:
  Game() {}

  void setGrid(Grid&& grid);  // Use move semantics
  void move(Direction dir);
  void addRandomTile();

  bool isGameOver() const;
  bool hasWon() const;

  Grid& getGrid() { return grid; }
};