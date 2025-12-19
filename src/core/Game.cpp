#include "game.hpp"


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
    // 1. First slide: compress all tiles toward the chosen direction
    bool moved = grid.move(dir);

    // 2. Merge: combine adjacent tiles with the same value
    //    (each tile can merge only once per move)
    grid.mergeTiles(dir);

    // 3. Second slide: after merging, gaps appear → compress again
    bool movedAfterMerge = grid.move(dir);

    // 4. If anything moved or merged, spawn a new tile
    if (moved || movedAfterMerge) {
        addRandomTile();
    }

     // if (grid.move(dir)) {
    //     grid.mergeTiles(dir);   
    //     grid.move(dir);         
    //     addRandomTile();        
    // }
}

