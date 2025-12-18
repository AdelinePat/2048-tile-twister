#include "GameObject.hpp"

GameObject::GameObject(SDL_Renderer* renderer, float x, float y, float width, float height)
    : renderer(renderer), x(x), y(y), width(width), height(height) {
}

void GameObject::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameObject::setSize(float width, float height) {
    this->width = width;
    this->height = height;
}