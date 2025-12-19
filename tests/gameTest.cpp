// Configure doctest
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
// ... your tests
#include <iostream>

// Include the real project headers
#include "core/game.hpp"
#include "core/grid.hpp"
#include "core/tile.hpp"

// --------------------------------------------------
// UNIT TESTS - Basic functionality
// --------------------------------------------------
TEST_CASE(
    "Grid canMove returns false when grid is full and no merges possible") {
  std::cout << "Testing: Game over detection..." << std::endl;
  Game game;
  Grid grid;

  // Create a grid with no possible moves (checkerboard pattern)
  // No adjacent tiles have the same value
  int values[4][4] = {{2, 4, 2, 4}, {4, 2, 4, 2}, {2, 4, 2, 4}, {4, 2, 4, 2}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid.addTile(new Tile(values[i][j], i, j));
    }
  }
  //   game.setGrid(grid);
  game.setGrid(std::move(grid));

  CHECK_MESSAGE(game.getGrid().hasEmptyCell() == false, "Grid should be full");
  CHECK_MESSAGE(game.getGrid().canMerge() == false,
                "No adjacent tiles should be able to merge");
  CHECK_MESSAGE(game.getGrid().canMove() == false,
                "Cannot move since grid is full and can't merge");
  CHECK_MESSAGE(game.isGameOver() == true, "Game should be over");

  std::cout << "  ✓ Game over detection works correctly" << std::endl;
}

TEST_CASE("Game detects win condition when 2048 tile exists") {
  std::cout << "Testing: Win detection..." << std::endl;
  Game game;
  Grid grid;

  // Create a grid with a 2048 tile
  int values[4][4] = {
      {2048, 1024, 2, 4}, {4, 2, 4, 2}, {2, 4, 2, 4}, {4, 2, 4, 2}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid.addTile(new Tile(values[i][j], i, j));
    }
  }
  //   game.setGrid(grid);
  game.setGrid(std::move(grid));

  CHECK_MESSAGE(game.hasWon() == true, "Game should be won with 2048 tile");

  std::cout << "  ✓ Win detection works correctly" << std::endl;
}