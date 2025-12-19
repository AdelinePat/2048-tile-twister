#include "grid.hpp"
#include <cstdlib>
#include <ctime>

bool Grid::move(Direction dir) {
  bool moved = false;
  resetAllMergeStates();
  
  slideTiles(dir, moved);
  mergeTiles(dir);
  slideTiles(dir, moved);
  
  return moved;
}

void Grid::resetAllMergeStates() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j]) {
        tiles[i][j]->resetMergeState();
      }
    }
  }
}

void Grid::slideTiles(Direction dir, bool& moved) {
  switch (dir) {
    case Direction::LEFT:   slideLeft(moved);  break;
    case Direction::RIGHT:  slideRight(moved); break;
    case Direction::UP:     slideUp(moved);    break;
    case Direction::DOWN:   slideDown(moved);  break;
  }
}

void Grid::slideLeft(bool& moved) {
  for (int i = 0; i < 4; i++) {
    int target = 0;
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j]) {
        if (j != target) {
          tiles[i][target] = std::move(tiles[i][j]);
          tiles[i][target]->setPosition(i, target);
          moved = true;
        }
        target++;
      }
    }
  }
}

void Grid::slideRight(bool& moved) {
  for (int i = 0; i < 4; i++) {
    int target = 3;
    for (int j = 3; j >= 0; j--) {
      if (tiles[i][j]) {
        if (j != target) {
          tiles[i][target] = std::move(tiles[i][j]);
          tiles[i][target]->setPosition(i, target);
          moved = true;
        }
        target--;
      }
    }
  }
}

void Grid::slideUp(bool& moved) {
  for (int j = 0; j < 4; j++) {
    int target = 0;
    for (int i = 0; i < 4; i++) {
      if (tiles[i][j]) {
        if (i != target) {
          tiles[target][j] = std::move(tiles[i][j]);
          tiles[target][j]->setPosition(target, j);
          moved = true;
        }
        target++;
      }
    }
  }
}

void Grid::slideDown(bool& moved) {
  for (int j = 0; j < 4; j++) {
    int target = 3;
    for (int i = 3; i >= 0; i--) {
      if (tiles[i][j]) {
        if (i != target) {
          tiles[target][j] = std::move(tiles[i][j]);
          tiles[target][j]->setPosition(target, j);
          moved = true;
        }
        target--;
      }
    }
  }
}

void Grid::mergeLeft() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (tiles[i][j] && tiles[i][j + 1] && 
          tiles[i][j]->canMergeWith(tiles[i][j + 1].get())) {
        tiles[i][j]->doubleValue();
        tiles[i][j]->setMerged(true);
        tiles[i][j + 1].reset();  // Automatically deletes
      }
    }
  }
}

void Grid::mergeRight() {
  for (int i = 0; i < 4; i++) {
    for (int j = 3; j > 0; j--) {
      if (tiles[i][j] && tiles[i][j - 1] && 
          tiles[i][j]->canMergeWith(tiles[i][j - 1].get())) {
        tiles[i][j]->doubleValue();
        tiles[i][j]->setMerged(true);
        tiles[i][j - 1].reset();
      }
    }
  }
}

void Grid::mergeUp() {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 3; i++) {
      if (tiles[i][j] && tiles[i + 1][j] && 
          tiles[i][j]->canMergeWith(tiles[i + 1][j].get())) {
        tiles[i][j]->doubleValue();
        tiles[i][j]->setMerged(true);
        tiles[i + 1][j].reset();
      }
    }
  }
}

void Grid::mergeDown() {
  for (int j = 0; j < 4; j++) {
    for (int i = 3; i > 0; i--) {
      if (tiles[i][j] && tiles[i - 1][j] && 
          tiles[i][j]->canMergeWith(tiles[i - 1][j].get())) {
        tiles[i][j]->doubleValue();
        tiles[i][j]->setMerged(true);
        tiles[i - 1][j].reset();
      }
    }
  }
}

void Grid::mergeTiles(Direction dir) {
  switch (dir) {
    case Direction::LEFT:   mergeLeft();  break;
    case Direction::RIGHT:  mergeRight(); break;
    case Direction::UP:     mergeUp();    break;
    case Direction::DOWN:   mergeDown();  break;
  }
}

bool Grid::isCellEmpty() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!tiles[i][j]) return true;
    }
  }
  return false;
}

bool Grid::canMerge() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j]) {
        if (j < 3 && tiles[i][j]->canMergeWith(tiles[i][j + 1].get()))
          return true;
        if (i < 3 && tiles[i][j]->canMergeWith(tiles[i + 1][j].get()))
          return true;
      }
    }
  }
  return false;
}

bool Grid::canMove() const {
  return isCellEmpty() || canMerge();
}

bool Grid::hasValue(int targetValue) const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] && tiles[i][j]->getValue() >= targetValue) {
        return true;
      }
    }
  }
  return false;
}

std::vector<std::pair<int, int>> Grid::getEmptyCells() const {
  std::vector<std::pair<int, int>> emptyCells;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!tiles[i][j]) {
        emptyCells.push_back({i, j});
      }
    }
  }
  return emptyCells;
}

void Grid::addTile(Tile* tile) {
  if (tile) {
    int x = tile->getX();
    int y = tile->getY();
    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
      tiles[x][y].reset(tile);  // Smart pointer takes ownership
    }
  }
}

void Grid::addRandomTile() {
  auto emptyCells = getEmptyCells();
  
  if (!emptyCells.empty()) {
    static bool seeded = false;
    if (!seeded) {
      std::srand(static_cast<unsigned int>(std::time(nullptr)));
      seeded = true;
    }
    
    auto [i, j] = emptyCells[std::rand() % emptyCells.size()];
    int val = (std::rand() % 10 < 9) ? 2 : 4;
    tiles[i][j] = std::make_unique<Tile>(val, i, j);
  }
}

void Grid::clear() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tiles[i][j].reset();  // Deletes and sets to nullptr
    }
  }
}