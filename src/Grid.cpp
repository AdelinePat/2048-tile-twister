#include "Grid.hpp"
#include <random>
#include <algorithm>

Grid::Grid() : score(0), won(false) {
    reset();
}

void Grid::reset() {
    // Initialize all tiles as empty
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            tiles[row][col] = std::make_shared<Tile>(0);
        }
    }
    
    score = 0;
    won = false;
    
    // Add two starting tiles
    addRandomTile();
    addRandomTile();
}

std::shared_ptr<Tile> Grid::getTile(int row, int col) const {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return tiles[row][col];
    }
    return nullptr;
}

void Grid::setTile(int row, int col, std::shared_ptr<Tile> tile) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        tiles[row][col] = tile;
    }
}

bool Grid::move(Direction dir) {
    bool moved = false;
    
    switch (dir) {
        case Direction::LEFT:
            moved = moveLeft();
            break;
        case Direction::RIGHT:
            moved = moveRight();
            break;
        case Direction::UP:
            moved = moveUp();
            break;
        case Direction::DOWN:
            moved = moveDown();
            break;
    }
    
    if (moved) {
        clearMergeFlags();
        addRandomTile();
    }
    
    return moved;
}

bool Grid::moveLeft() {
    bool moved = false;
    
    for (int row = 0; row < SIZE; ++row) {
        std::vector<std::shared_ptr<Tile>> line;
        for (int col = 0; col < SIZE; ++col) {
            line.push_back(tiles[row][col]);
        }
        
        if (slideAndMerge(line)) {
            moved = true;
            for (int col = 0; col < SIZE; ++col) {
                tiles[row][col] = line[col];
            }
        }
    }
    
    return moved;
}

bool Grid::moveRight() {
    bool moved = false;
    
    for (int row = 0; row < SIZE; ++row) {
        std::vector<std::shared_ptr<Tile>> line;
        for (int col = SIZE - 1; col >= 0; --col) {
            line.push_back(tiles[row][col]);
        }
        
        if (slideAndMerge(line)) {
            moved = true;
            for (int col = 0; col < SIZE; ++col) {
                tiles[row][SIZE - 1 - col] = line[col];
            }
        }
    }
    
    return moved;
}

bool Grid::moveUp() {
    bool moved = false;
    
    for (int col = 0; col < SIZE; ++col) {
        std::vector<std::shared_ptr<Tile>> line;
        for (int row = 0; row < SIZE; ++row) {
            line.push_back(tiles[row][col]);
        }
        
        if (slideAndMerge(line)) {
            moved = true;
            for (int row = 0; row < SIZE; ++row) {
                tiles[row][col] = line[row];
            }
        }
    }
    
    return moved;
}

bool Grid::moveDown() {
    bool moved = false;
    
    for (int col = 0; col < SIZE; ++col) {
        std::vector<std::shared_ptr<Tile>> line;
        for (int row = SIZE - 1; row >= 0; --row) {
            line.push_back(tiles[row][col]);
        }
        
        if (slideAndMerge(line)) {
            moved = true;
            for (int row = 0; row < SIZE; ++row) {
                tiles[SIZE - 1 - row][col] = line[row];
            }
        }
    }
    
    return moved;
}

bool Grid::slideAndMerge(std::vector<std::shared_ptr<Tile>>& line) {
    bool changed = false;
    std::vector<std::shared_ptr<Tile>> newLine;
    
    // Extract non-empty tiles
    for (auto& tile : line) {
        if (!tile->isEmpty()) {
            newLine.push_back(tile);
        }
    }
    
    // Merge adjacent equal tiles
    for (size_t i = 0; i < newLine.size(); ++i) {
        if (i + 1 < newLine.size() && newLine[i]->canMergeWith(*newLine[i + 1])) {
            newLine[i]->mergeWith(*newLine[i + 1]);
            score += newLine[i]->getValue();
            
            if (newLine[i]->getValue() == 2048) {
                won = true;
            }
            
            newLine.erase(newLine.begin() + i + 1);
            changed = true;
        }
    }
    
    // Fill remaining spaces with empty tiles
    while (newLine.size() < SIZE) {
        newLine.push_back(std::make_shared<Tile>(0));
    }
    
    // Check if anything changed
    for (size_t i = 0; i < SIZE; ++i) {
        if (line[i]->getValue() != newLine[i]->getValue()) {
            changed = true;
        }
    }
    
    line = newLine;
    return changed;
}

void Grid::clearMergeFlags() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            tiles[row][col]->setMerged(false);
            tiles[row][col]->setNew(false);
        }
    }
}

std::vector<std::pair<int, int>> Grid::getEmptyCells() const {
    std::vector<std::pair<int, int>> empty;
    
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (tiles[row][col]->isEmpty()) {
                empty.push_back({row, col});
            }
        }
    }
    
    return empty;
}

void Grid::addRandomTile() {
    auto emptyCells = getEmptyCells();
    
    if (emptyCells.empty()) {
        return;
    }
    
    // Random number generation
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Pick random empty cell
    std::uniform_int_distribution<> cellDist(0, emptyCells.size() - 1);
    auto [row, col] = emptyCells[cellDist(gen)];
    
    // 90% chance of 2, 10% chance of 4
    std::uniform_int_distribution<> valueDist(0, 9);
    int value = (valueDist(gen) < 9) ? 2 : 4;
    
    tiles[row][col] = std::make_shared<Tile>(value);
}

bool Grid::canMove() const {
    // Check for empty cells
    if (!getEmptyCells().empty()) {
        return true;
    }
    
    // Check for possible merges
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            // Check right neighbor
            if (col < SIZE - 1 && tiles[row][col]->getValue() == tiles[row][col + 1]->getValue()) {
                return true;
            }
            // Check down neighbor
            if (row < SIZE - 1 && tiles[row][col]->getValue() == tiles[row + 1][col]->getValue()) {
                return true;
            }
        }
    }
    
    return false;
}

bool Grid::hasWon() const {
    return won;
}

bool Grid::isGameOver() const {
    return !canMove();
}