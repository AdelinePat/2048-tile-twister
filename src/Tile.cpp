#include "Tile.hpp"

Tile::Tile(int value) 
    : value(value), merged(false), newTile(value != 0) {
}

bool Tile::canMergeWith(const Tile& other) const {
    // Can only merge if both tiles have same non-zero value
    // and neither has been merged this turn
    return !isEmpty() && 
           !other.isEmpty() && 
           value == other.value && 
           !merged && 
           !other.merged;
}

void Tile::mergeWith(const Tile& other) {
    value += other.value;
    merged = true;
    newTile = false;
}