#pragma once
#include <SDL3/SDL.h>

class GameObject {
 protected:
  int x, y, width, height;

 public:
  GameObject(int x, int y, int width, int height);
  /**
   * @brief Virtual destructor
   */
  virtual ~GameObject() = default;
  /**
   * @brief Render the object (pure virtual)
   * @param renderer SDL renderer
   */
  virtual void render(
      SDL_Renderer* renderer) = 0;
  int getX();
  int getY();
  int getWidth();
  int getHeight();
};
