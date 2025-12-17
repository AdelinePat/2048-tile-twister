#include "Tile.hpp"

Tile::Tile(int v, int posX, int posY)
    : value(v), x(posX), y(posY) {}

int Tile::getValue() const {return value;}
void Tile::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}


std::pair<int,int> Tile::getPosition() const {return {x, y};}
