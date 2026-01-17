#include "tile.hpp"

Tile::Tile(int value, int posX, int posY)
    : value(value), x(posX), y(posY), merged(false) {}

int Tile::getValue() const { return value; }

void Tile::setValue(int newVal) { value = newVal; }

void Tile::doubleValue() { value *= 2; }

void Tile::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

std::pair<int, int> Tile::getPosition() const { 
    return {x, y}; 
}

bool Tile::canMergeWith(const Tile* other) const {
    if (!other) return false;
    return value == other->value && !merged && !other->merged;
}
