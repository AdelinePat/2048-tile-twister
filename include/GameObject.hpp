#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL3/SDL.h>

/**
 * GameObject - Base class for all renderable objects
 * Manages position, size, and provides rendering interface
 */
class GameObject {
public:
    GameObject(SDL_Renderer* renderer, float x, float y, float width, float height);
    virtual ~GameObject() = default;

    // Pure virtual render function - must be implemented by derived classes
    virtual void render() = 0;

    // Position and size getters/setters
    void setPosition(float x, float y);
    void setSize(float width, float height);

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

protected:
    SDL_Renderer* renderer;
    float x, y;
    float width, height;
};

#endif // GAMEOBJECT_HPP