#include "grid.hpp"

#include <cstdlib>
#include <ctime>

Grid::Grid() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tiles[i][j] = nullptr;
}

bool Grid::move(Direction dir) {
  bool moved = false;

  slideTiles(dir, moved);
  mergeTiles(dir);

  // 3. Slide again to fill gaps from merges
  slideTiles(dir, moved);

  return moved;
}

void Grid::slideTiles(Direction dir, bool& moved) {
  switch (dir) {
    case Direction::LEFT:
      slideLeft(moved);
      break;
    case Direction::RIGHT:
      slideRight(moved);
      break;
    case Direction::UP:
      slideUp(moved);
      break;
    case Direction::DOWN:
      slideDown(moved);
      break;
  }
}

// --- Slide helpers ---
void Grid::slideLeft(bool& moved) {
  for (int i = 0; i < 4; i++) {
    int target = 0;
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] != nullptr) {
        if (j != target) {
          tiles[i][target] = tiles[i][j];
          tiles[i][target]->setPosition(i, target);
          tiles[i][j] = nullptr;
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
      if (tiles[i][j] != nullptr) {
        if (j != target) {
          tiles[i][target] = tiles[i][j];
          tiles[i][target]->setPosition(i, target);
          tiles[i][j] = nullptr;
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
      if (tiles[i][j] != nullptr) {
        if (i != target) {
          tiles[target][j] = tiles[i][j];
          tiles[target][j]->setPosition(target, j);
          tiles[i][j] = nullptr;
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
      if (tiles[i][j] != nullptr) {
        if (i != target) {
          tiles[target][j] = tiles[i][j];
          tiles[target][j]->setPosition(target, j);
          tiles[i][j] = nullptr;
          moved = true;
        }
        target--;
      }
    }
  }
}

bool Grid::isCellEmpty() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] == nullptr) return true;
    }
  }
  return false;
}

bool Grid::canMerge() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] != nullptr) {
        if (i < 3 && tiles[i + 1][j] != nullptr &&
            tiles[i][j]->getValue() == tiles[i + 1][j]->getValue())
          return true;
        if (j < 3 && tiles[i][j + 1] != nullptr &&
            tiles[i][j]->getValue() == tiles[i][j + 1]->getValue())
          return true;
      }
    }
  }
  return false;
}

bool Grid::canMove() const {
  // Case vide ?
  // bool empty = isCellEmpty();
  // if (isCellEmpty()) {
  //   return true;
  // }
  // return canMerge();
  return isCellEmpty() || canMerge();
}

void Grid::addTile(Tile* tile) {
  if (tile) {
    int x = tile->getPosition().first;
    int y = tile->getPosition().second;
    tiles[x][y] = tile;
  }
}

void Grid::addRandomTile() {
  std::vector<std::pair<int, int>> emptyCells;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] == nullptr) {
        emptyCells.push_back({i, j});
      }
    }
  }

  if (!emptyCells.empty()) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    auto [i, j] = emptyCells[std::rand() % emptyCells.size()];
    int val = (std::rand() % 2 == 0) ? 2 : 4;
    tiles[i][j] = new Tile(val, i, j);
  }
}

// rendering is now handled by GridView

void Grid::mergeLeft() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (tiles[i][j] != nullptr && tiles[i][j + 1] != nullptr &&
          tiles[i][j]->getValue() == tiles[i][j + 1]->getValue()) {
        tiles[i][j]->setValue(tiles[i][j]->getValue() * 2);
        delete tiles[i][j + 1];
        tiles[i][j + 1] = nullptr;
      }
    }
  }
}

void Grid::mergeRight() {
  for (int i = 0; i < 4; i++) {
    for (int j = 3; j > 0; j--) {
      if (tiles[i][j] != nullptr && tiles[i][j - 1] != nullptr &&
          tiles[i][j]->getValue() == tiles[i][j - 1]->getValue()) {
        tiles[i][j]->setValue(tiles[i][j]->getValue() * 2);
        delete tiles[i][j - 1];
        tiles[i][j - 1] = nullptr;
      }
    }
  }
}

void Grid::mergeUp() {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 3; i++) {
      if (tiles[i][j] != nullptr && tiles[i + 1][j] != nullptr &&
          tiles[i][j]->getValue() == tiles[i + 1][j]->getValue()) {
        tiles[i][j]->setValue(tiles[i][j]->getValue() * 2);
        delete tiles[i + 1][j];
        tiles[i + 1][j] = nullptr;
      }
    }
  }
}

void Grid::mergeDown() {
  for (int j = 0; j < 4; j++) {
    for (int i = 3; i > 0; i--) {
      if (tiles[i][j] != nullptr && tiles[i - 1][j] != nullptr &&
          tiles[i][j]->getValue() == tiles[i - 1][j]->getValue()) {
        tiles[i][j]->setValue(tiles[i][j]->getValue() * 2);
        delete tiles[i - 1][j];
        tiles[i - 1][j] = nullptr;
      }
    }
  }
}

void Grid::mergeTiles(Direction dir) {
  switch (dir) {
    case Direction::LEFT:
      this->mergeLeft();
      break;

    case Direction::RIGHT:
      this->mergeRight();
      break;

    case Direction::UP:
      this->mergeUp();
      break;

    case Direction::DOWN:
      this->mergeDown();
      break;
  }
}
