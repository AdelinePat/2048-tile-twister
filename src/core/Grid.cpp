#include "grid.hpp"

#include <cstdlib>
#include <ctime>
#include <functional>

Grid::Grid() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tiles[i][j] = nullptr;
}

bool Grid::move(Direction dir) {
  bool moved = false;

  // Helper lambdas for sliding
  std::function<void()> slideLeft = [&]() {
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
  };
  std::function<void()> slideRight = [&]() {
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
  };
  std::function<void()> slideUp = [&]() {
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
  };
  std::function<void()> slideDown = [&]() {
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
  };

  // 1. Slide
  switch (dir) {
    case Direction::LEFT:
      slideLeft();
      break;
    case Direction::RIGHT:
      slideRight();
      break;
    case Direction::UP:
      slideUp();
      break;
    case Direction::DOWN:
      slideDown();
      break;
  }

  // 2. Merge
  mergeTiles(dir);

  // 3. Slide again to fill gaps

  switch (dir) {
    case Direction::LEFT:
      slideLeft();
      break;
    case Direction::RIGHT:
      slideRight();
      break;
    case Direction::UP:
      slideUp();
      break;
    case Direction::DOWN:
      slideDown();
      break;
  }

  return moved;
}

bool Grid::canMove() const {
  // Case vide ?
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tiles[i][j] == nullptr) return true;
    }
  }

  // Fusion possible ?
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

void Grid::mergeTiles(Direction dir) {
  switch (dir) {
    case Direction::LEFT:
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
      break;

    case Direction::RIGHT:
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
      break;

    case Direction::UP:
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
      break;

    case Direction::DOWN:
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
      break;
  }
}
