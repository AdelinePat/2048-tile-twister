// Configure doctest
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <iostream>

// Include the real project headers
#include "core/grid.hpp"
#include "core/tile.hpp"

// --------------------------------------------------
// UNIT TESTS - Basic functionality
// --------------------------------------------------

TEST_CASE("Grid initializes empty") {
  std::cout << "Testing: Grid initialization..." << std::endl;
  
  Grid grid;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      CHECK_MESSAGE(grid.getTile(i, j) == nullptr, "Cell should be null at start");
    }
  }

  CHECK_MESSAGE(grid.hasEmptyCell() == true, "Grid should have empty cells");
  CHECK_MESSAGE(grid.canMove() == true, "Empty grid should allow moves");
  
  std::cout << "  ✓ Grid initializes correctly" << std::endl;
}

TEST_CASE("Grid move LEFT shifts tiles without merge") {
  std::cout << "Testing: LEFT movement..." << std::endl;
  
  Grid grid;

  // Arrange: Place tiles at (0,1) and (0,3)
  grid.addTile(new Tile(2, 0, 1));
  grid.addTile(new Tile(4, 0, 3));

  // Act: Move left
  bool moved = grid.move(Direction::LEFT);

  // Assert: Tiles should shift to (0,0) and (0,1)
  CHECK_MESSAGE(moved == true, "Move should return true");
  CHECK_MESSAGE(grid.getTile(0, 0) != nullptr, "Tile should exist at (0,0)");
  CHECK_MESSAGE(grid.getTile(0, 0)->getValue() == 2, "Tile at (0,0) should be 2");
  CHECK_MESSAGE(grid.getTile(0, 1) != nullptr, "Tile should exist at (0,1)");
  CHECK_MESSAGE(grid.getTile(0, 1)->getValue() == 4, "Tile at (0,1) should be 4");
  CHECK_MESSAGE(grid.getTile(0, 2) == nullptr, "Tile at (0,2) should be empty");
  CHECK_MESSAGE(grid.getTile(0, 3) == nullptr, "Tile at (0,3) should be empty");
  
  std::cout << "  ✓ LEFT movement works correctly" << std::endl;
}

TEST_CASE("Grid move RIGHT shifts tiles correctly") {
  std::cout << "Testing: RIGHT movement..." << std::endl;
  
  Grid grid;

  grid.addTile(new Tile(2, 1, 0));
  grid.addTile(new Tile(4, 1, 2));

  bool moved = grid.move(Direction::RIGHT);

  CHECK_MESSAGE(moved == true, "Move should return true");
  CHECK_MESSAGE(grid.getTile(1, 3) != nullptr, "Tile should exist at (1,3)");
  CHECK_MESSAGE(grid.getTile(1, 3)->getValue() == 4, "Tile at (1,3) should be 4");
  CHECK_MESSAGE(grid.getTile(1, 2) != nullptr, "Tile should exist at (1,2)");
  CHECK_MESSAGE(grid.getTile(1, 2)->getValue() == 2, "Tile at (1,2) should be 2");
  CHECK_MESSAGE(grid.getTile(1, 0) == nullptr, "Tile at (1,0) should be null");
  
  std::cout << "  ✓ RIGHT movement works correctly" << std::endl;
}

TEST_CASE("Grid move UP shifts tiles correctly") {
  std::cout << "Testing: UP movement..." << std::endl;
  
  Grid grid;

  grid.addTile(new Tile(2, 2, 0));
  grid.addTile(new Tile(4, 3, 0));

  bool moved = grid.move(Direction::UP);

  CHECK_MESSAGE(moved == true, "Move should return true");
  CHECK_MESSAGE(grid.getTile(0, 0) != nullptr, "Tile should exist at (0,0)");
  CHECK_MESSAGE(grid.getTile(0, 0)->getValue() == 2, "Tile at (0,0) should be 2");
  CHECK_MESSAGE(grid.getTile(1, 0) != nullptr, "Tile should exist at (1,0)");
  CHECK_MESSAGE(grid.getTile(1, 0)->getValue() == 4, "Tile at (1,0) should be 4");
  
  std::cout << "  ✓ UP movement works correctly" << std::endl;
}

TEST_CASE("Grid move DOWN shifts tiles correctly") {
  std::cout << "Testing: DOWN movement..." << std::endl;
  
  Grid grid;

  grid.addTile(new Tile(2, 0, 0));
  grid.addTile(new Tile(4, 1, 0));

  bool moved = grid.move(Direction::DOWN);

  CHECK_MESSAGE(moved == true, "Move should return true");
  CHECK_MESSAGE(grid.getTile(3, 0) != nullptr, "Tile should exist at (3,0)");
  CHECK_MESSAGE(grid.getTile(3, 0)->getValue() == 4, "Tile at (3,0) should be 4");
  CHECK_MESSAGE(grid.getTile(2, 0) != nullptr, "Tile should exist at (2,0)");
  CHECK_MESSAGE(grid.getTile(2, 0)->getValue() == 2, "Tile at (2,0) should be 2");
  
  std::cout << "  ✓ DOWN movement works correctly" << std::endl;
}

// --------------------------------------------------
// INTEGRATION TESTS - Move + Merge
// --------------------------------------------------

TEST_CASE("Grid LEFT merge combines equal tiles") {
  std::cout << "Testing: LEFT merge..." << std::endl;
  
  Grid grid;

  grid.addTile(new Tile(2, 0, 0));
  grid.addTile(new Tile(2, 0, 1));

  grid.move(Direction::LEFT);
  // grid.mergeTiles(Direction::LEFT);

  Tile* t = grid.getTile(0, 0);
  REQUIRE_MESSAGE(t != nullptr, "Merged tile should exist");
  CHECK_MESSAGE(t->getValue() == 4, "Merged tile should have value 4 (2+2)");
  CHECK_MESSAGE(grid.getTile(0, 1) == nullptr, "Second tile should be gone after merge");
  
  std::cout << "  ✓ LEFT merge works correctly" << std::endl;
}

TEST_CASE("Grid RIGHT merge combines equal tiles") {
  std::cout << "Testing: RIGHT merge..." << std::endl;
  
  Grid grid;

  grid.addTile(new Tile(4, 2, 2));
  grid.addTile(new Tile(4, 2, 3));

  grid.move(Direction::RIGHT);
  // grid.mergeTiles(Direction::RIGHT);

  Tile* t = grid.getTile(2, 3);
  REQUIRE_MESSAGE(t != nullptr, "Merged tile should exist");
  CHECK_MESSAGE(t->getValue() == 8, "Merged tile should have value 8 (4+4)");
  CHECK_MESSAGE(grid.getTile(2, 2) == nullptr, "First tile should be gone after merge");
  
  std::cout << "  ✓ RIGHT merge works correctly" << std::endl;
}

// --------------------------------------------------
// GAME OVER DETECTION
// --------------------------------------------------

TEST_CASE("Grid canMove returns false when grid is full and no merges possible") {
  std::cout << "Testing: Game over detection..." << std::endl;
  
  Grid grid;

  // Create a grid with no possible moves (checkerboard pattern)
  int values[4][4] = {
    {2, 4, 2, 4}, 
    {4, 2, 4, 2}, 
    {2, 4, 2, 4}, 
    {4, 2, 4, 2}
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid.addTile(new Tile(values[i][j], i, j));
    }
  }

  CHECK_MESSAGE(grid.hasEmptyCell() == false, "Grid should be full");
  CHECK_MESSAGE(grid.canMerge() == false, "No adjacent tiles can merge");
  CHECK_MESSAGE(grid.canMove() == false, "Game should be over");
  
  std::cout << "  ✓ Game over detection works correctly" << std::endl;
}

TEST_CASE("Grid canMove returns true when merges are possible") {
  std::cout << "Testing: Merge detection..." << std::endl;
  
  Grid grid;

  // Create a grid with possible merges
  int values[4][4] = {
    {2, 2, 4, 8},  // Two 2s can merge
    {4, 8, 2, 4}, 
    {2, 4, 8, 2}, 
    {8, 2, 4, 16}
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid.addTile(new Tile(values[i][j], i, j));
    }
  }

  CHECK_MESSAGE(grid.hasEmptyCell() == false, "Grid should be full");
  CHECK_MESSAGE(grid.canMerge() == true, "Adjacent 2s should be mergeable");
  CHECK_MESSAGE(grid.canMove() == true, "Game should NOT be over");
  
  std::cout << "  ✓ Merge detection works correctly" << std::endl;
}