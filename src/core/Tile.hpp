#pragma once
#include <iostream>

class Tile {
 private:
  int value;
  int x;
  int y;
  bool merged;  // Track if tile was merged this turn

 public:
  Tile(int v, int posX, int posY);
  
  // Value operations
  int getValue() const;
  void setValue(int newVal);
  void doubleValue();  // For merging
  
  // Position operations
  std::pair<int, int> getPosition() const;
  void setPosition(int newX, int newY);
  int getX() const { return x; }
  int getY() const { return y; }
  
  // Merge state
  bool hasMerged() const { return merged; }
  void setMerged(bool state) { merged = state; }
  void resetMergeState() { merged = false; }
  
  // Tile comparison
  bool canMergeWith(const Tile* other) const;
};