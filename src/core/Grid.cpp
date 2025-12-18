#include "grid.hpp"

#include <cstdlib>
#include <ctime>

Grid::Grid() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tiles[i][j] = nullptr;
}

bool Grid::move(Direction dir) {
  bool moved = false;

  auto slideAndMerge = [&](auto get, auto set) {
    for (int i = 0; i < 4; ++i) {
      // Slide tiles
      int pos = 0;
      for (int j = 0; j < 4; ++j) {
        Tile* t = get(i, j);
        if (t) {
          if (j != pos) {
            set(i, pos, t);
            set(i, j, nullptr);
            t->setPosition(
                (dir == Direction::LEFT || dir == Direction::RIGHT) ? i : pos,
                (dir == Direction::LEFT || dir == Direction::RIGHT) ? pos : i);
            moved = true;
          }
          pos++;
        }
      }
      // Merge tiles
      for (int j = 0; j < 3; ++j) {
        Tile* t1 = get(i, j);
        Tile* t2 = get(i, j + 1);
        if (t1 && t2 && t1->getValue() == t2->getValue()) {
          t1->setValue(t1->getValue() * 2);
          delete t2;
          set(i, j + 1, nullptr);
          moved = true;
        }
      }
      // Slide again after merge
      pos = 0;
      for (int j = 0; j < 4; ++j) {
        Tile* t = get(i, j);
        if (t) {
          if (j != pos) {
            set(i, pos, t);
            set(i, j, nullptr);
            t->setPosition(
                (dir == Direction::LEFT || dir == Direction::RIGHT) ? i : pos,
                (dir == Direction::LEFT || dir == Direction::RIGHT) ? pos : i);
          }
          pos++;
        }
      }
    }
  };

  switch (dir) {
    case Direction::LEFT:
      slideAndMerge([&](int i, int j) { return tiles[i][j]; },
                    [&](int i, int j, Tile* t) { tiles[i][j] = t; });
      break;
    case Direction::RIGHT:
      slideAndMerge([&](int i, int j) { return tiles[i][3 - j]; },
                    [&](int i, int j, Tile* t) { tiles[i][3 - j] = t; });
      break;
    case Direction::UP:
      slideAndMerge([&](int i, int j) { return tiles[j][i]; },
                    [&](int i, int j, Tile* t) { tiles[j][i] = t; });
      break;
    case Direction::DOWN:
      slideAndMerge([&](int i, int j) { return tiles[3 - j][i]; },
                    [&](int i, int j, Tile* t) { tiles[3 - j][i] = t; });
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
