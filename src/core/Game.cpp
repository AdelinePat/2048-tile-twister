#include "game.hpp"

// bool Game::move(Direction dir) { return grid.move(dir); }

void Game::addRandomTile() { grid.addRandomTile(); }

bool Game::isGameOver() const { 
    return !grid.canMove(); }

bool Game::hasWon() const {
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            Tile* tile= grid.getTile(i, j);
            if(tile && tile ->getValue() >= 2048) {
                return true;
            }
        }
    }
    return false;
}

Grid& Game::getGrid() { return grid; }


void Game::move(Direction dir) {
    bool moved = grid.move(dir);
    grid.mergeTiles(dir);
    bool movedAfterMerge = grid.move(dir);
    if(moved || movedAfterMerge) {
        addRandomTile();
    }
    // if (grid.move(dir)) {
    //     grid.mergeTiles(dir);   
    //     grid.move(dir);         
    //     addRandomTile();        
    // }
}
