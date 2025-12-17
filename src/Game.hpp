#pragma once
#include "Grid.hpp"

class Game {
private:
    Grid grid;

public:
    void move(Direction dir);
    void addRandomTile();
    bool isGameOver() const;
    Grid& getGrid();
};
