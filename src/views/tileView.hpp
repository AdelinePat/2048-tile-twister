#pragma once
#include <iostream>
#include <SDL3/SDL.h>

#include <string>

#include "gameObject.hpp"

class TileView : public GameObject {
  int value;

 public:
  TileView(int x, int y, int width, int height, int value)
      : GameObject(x, y, width, height), value(value) {}
  void setValue(int v) { value = v; }
  int getValue() const { return value; }
  void render(SDL_Renderer* renderer) override;
};
