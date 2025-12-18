#ifndef GRID_HPP
#define GRID_HPP

#include "Tile.hpp"
#include <memory>
#include <vector>
#include <array>

/**
 * Grid - Game logic for the 2048 grid
 * Manages tile positions, movements, merging, and game state
 */
class Grid {
public:
    static constexpr int SIZE = 4;

    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Grid();

    // Game logic
    bool move(Direction dir);
    void addRandomTile();
    bool canMove() const;
    bool hasWon() const;
    bool isGameOver() const;

    // Grid access
    std::shared_ptr<Tile> getTile(int row, int col) const;
    void setTile(int row, int col, std::shared_ptr<Tile> tile);

    // Score
    int getScore() const { return score; }

    // Reset game
    void reset();

private:
    std::array<std::array<std::shared_ptr<Tile>, SIZE>, SIZE> tiles;
    int score;
    bool won;

    // Movement helpers
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();

    // Helper to slide and merge a single row/column
    bool slideAndMerge(std::vector<std::shared_ptr<Tile>>& line);

    // Clear merge flags after each move
    void clearMergeFlags();

    // Find empty cells
    std::vector<std::pair<int, int>> getEmptyCells() const;
};

#endif // GRID_HPP