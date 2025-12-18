#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Grid.hpp"
#include "GridView.hpp"
#include <memory>

/**
 * Game - Main controller class
 * Coordinates game logic, rendering, and input handling
 * Implements the main game loop
 */
class Game {
public:
    Game();
    ~Game() = default;
    
    bool init();
    void run();
    void cleanup();

private:
    std::unique_ptr<Window> window;
    std::shared_ptr<Grid> grid;
    std::shared_ptr<GridView> gridView;
    
    bool running;
    
    void handleEvents();
    void update();
    void render();
    void handleKeyPress(SDL_Keycode key);
};

#endif // GAME_HPP