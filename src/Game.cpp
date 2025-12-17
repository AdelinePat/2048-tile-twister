#include "Game.hpp"

void Game::move(Direction dir) {
    grid.move(dir);
}

void Game::addRandomTile() {
    grid.addRandomTile();
}

bool Game::isGameOver() const {
    return !grid.canMove();
}

Grid& Game::getGrid() {
    return grid;
}
