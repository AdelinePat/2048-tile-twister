#include "game.hpp"

void Game::addRandomTile() { 
  grid.addRandomTile(); 
}

bool Game::isGameOver() const { 
  return !grid.canMove(); 
}

bool Game::hasWon() const {
  if (won) return true;  // Once won, always won
  return grid.hasValue(2048);
}

void Game::move(Direction dir) {
  if (grid.move(dir)) {
    addRandomTile();
  }
}

void Game::setGrid(Grid&& newGrid) { 
  grid = std::move(newGrid); 
}