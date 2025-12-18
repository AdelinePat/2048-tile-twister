#ifndef TILE_HPP
#define TILE_HPP

/**
 * Tile - Pure logic class for a single tile
 * Holds the value and state, no rendering logic
 */
class Tile {
public:
    Tile(int value = 0);

    int getValue() const { return value; }
    void setValue(int value) { this->value = value; }

    bool isEmpty() const { return value == 0; }

    // Check if this tile can merge with another
    bool canMergeWith(const Tile& other) const;

    // Merge with another tile (doubles the value)
    void mergeWith(const Tile& other);

    // For tracking if tile was just merged (to prevent double merging in one move)
    bool wasMerged() const { return merged; }
    void setMerged(bool merged) { this->merged = merged; }

    // For tracking if tile is new (for animation purposes)
    bool isNew() const { return newTile; }
    void setNew(bool isNew) { this->newTile = isNew; }

private:
    int value;
    bool merged;    // Tracks if merged this turn
    bool newTile;   // Tracks if this is a newly spawned tile
};

#endif // TILE_HPP