#pragma once
#include "grid.hpp"

class Game {
 private:
  Grid grid;

 public:
 void move(Direction dir); 
  void addRandomTile();
  bool isGameOver() const;
  bool hasWon() const;
  Grid& getGrid();
};
