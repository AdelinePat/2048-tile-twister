#pragma once
#include "grid.hpp"

class Game {
 private:
  Grid grid;
  int score;
  bool won;

 public:
  Game() : score(0), won(false) {}
  
  void setGrid(Grid&& grid);  // Use move semantics
  void move(Direction dir);
  void addRandomTile();
  
  bool isGameOver() const;
  bool hasWon() const;
  
  Grid& getGrid() { return grid; }
  const Grid& getGrid() const { return grid; }
  
  int getScore() const { return score; }
  void addScore(int points) { score += points; }
};