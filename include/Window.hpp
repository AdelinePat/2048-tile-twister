#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <string>

/**
 * Window class - Manages SDL window and renderer
 * Handles window creation, destruction, and provides access to the renderer
 */
class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    // Delete copy constructor and assignment operator (SDL resources shouldn't be copied)
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool init();
    void clear();
    void present();

    SDL_Renderer* getRenderer() const { return renderer; }
    bool isOpen() const { return !shouldClose; }
    void close() { shouldClose = true; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::string title;
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool shouldClose;
};

#endif // WINDOW_HPP