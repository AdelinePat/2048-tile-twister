#include "Grid.hpp"
#include <cstdlib>
#include <ctime>

Grid::Grid() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tiles[i][j] = nullptr;
}


bool Grid::move(Direction dir) {
    bool moved = false;

    switch (dir) {
    case Direction::LEFT:
        for (int i = 0; i < 4; i++) {
            int target = 0;
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] != nullptr) {
                    if (j != target) {
                        tiles[i][target] = tiles[i][j];
                        tiles[i][target]->setPosition(i, target); // mise à jour
                        tiles[i][j] = nullptr;
                        moved = true;
                    }
                    target++;
                }
            }
        }
        break;

    case Direction::RIGHT:
        for (int i = 0; i < 4; i++) {
            int target = 3;
            for (int j = 3; j >= 0; j--) {
                if (tiles[i][j] != nullptr) {
                    if (j != target) {
                        tiles[i][target] = tiles[i][j];
                        tiles[i][target]->setPosition(i, target); // mise à jour
                        tiles[i][j] = nullptr;
                        moved = true;
                    }
                    target--;
                }
            }
        }
        break;

    case Direction::UP:
        for (int j = 0; j < 4; j++) {
            int target = 0;
            for (int i = 0; i < 4; i++) {
                if (tiles[i][j] != nullptr) {
                    if (i != target) {
                        tiles[target][j] = tiles[i][j];
                        tiles[target][j]->setPosition(target, j); // mise à jour
                        tiles[i][j] = nullptr;
                        moved = true;
                    }
                    target++;
                }
            }
        }
        break;

    case Direction::DOWN:
        for (int j = 0; j < 4; j++) {
            int target = 3;
            for (int i = 3; i >= 0; i--) {
                if (tiles[i][j] != nullptr) {
                    if (i != target) {
                        tiles[target][j] = tiles[i][j];
                        tiles[target][j]->setPosition(target, j); // mise à jour
                        tiles[i][j] = nullptr;
                        moved = true;
                    }
                    target--;
                }
            }
        }
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
                if (i < 3 && tiles[i+1][j] != nullptr &&
                    tiles[i][j]->getValue() == tiles[i+1][j]->getValue())
                    return true;
                if (j < 3 && tiles[i][j+1] != nullptr &&
                    tiles[i][j]->getValue() == tiles[i][j+1]->getValue())
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
    std::vector<std::pair<int,int>> emptyCells;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tiles[i][j] == nullptr) {
                emptyCells.push_back({i,j});
            }
        }
    }

    if (!emptyCells.empty()) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        auto [i,j] = emptyCells[std::rand() % emptyCells.size()];
        int val = (std::rand() % 2 == 0) ? 2 : 4;
        tiles[i][j] = new Tile(val, i, j);
    }
}

void Grid::render(SDL_Renderer* renderer) const {
    int cellSize = 100;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            SDL_FRect rect { j * cellSize, i * cellSize, cellSize, cellSize };

            if (tiles[i][j] != nullptr) {
                SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255); // jaune
            } else {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // gris
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
