#include "Game.hpp"
#include <iostream>

Game::Game() : running(false) {
}

bool Game::init() {
    // Create window
    window = std::make_unique<Window>("2048 Game", 600, 700);
    if (!window->init()) {
        return false;
    }
    
    // Create grid (game logic)
    grid = std::make_shared<Grid>();
    
    // Create grid view (visual representation)
    // Position grid in center with some margin for score display
    float gridSize = 500.0f;
    float gridX = (window->getWidth() - gridSize) / 2.0f;
    float gridY = 150.0f;
    
    gridView = std::make_shared<GridView>(
        window->getRenderer(), 
        grid, 
        gridX, 
        gridY, 
        gridSize
    );
    
    running = true;
    return true;
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint64 frameStart;
    int frameTime;
    
    while (running && window->isOpen()) {
        frameStart = SDL_GetTicks();
        
        handleEvents();
        update();
        render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::handleEvents() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                window->close();
                break;
                
            case SDL_EVENT_KEY_DOWN:
                handleKeyPress(event.key.key);
                break;
        }
    }
}

void Game::handleKeyPress(SDL_Keycode key) {
    Grid::Direction dir;
    bool validMove = false;
    
    switch (key) {
        case SDLK_UP:
        case SDLK_W:
            dir = Grid::Direction::UP;
            validMove = true;
            break;
            
        case SDLK_DOWN:
        case SDLK_S:
            dir = Grid::Direction::DOWN;
            validMove = true;
            break;
            
        case SDLK_LEFT:
        case SDLK_A:
            dir = Grid::Direction::LEFT;
            validMove = true;
            break;
            
        case SDLK_RIGHT:
        case SDLK_D:
            dir = Grid::Direction::RIGHT;
            validMove = true;
            break;
            
        case SDLK_R:
            // Reset game
            grid->reset();
            gridView->updateTileViews();
            std::cout << "Game reset!" << std::endl;
            break;
            
        case SDLK_ESCAPE:
            running = false;
            break;
    }
    
    if (validMove) {
        if (grid->move(dir)) {
            gridView->updateTileViews();
            std::cout << "Score: " << grid->getScore() << std::endl;
            
            if (grid->hasWon()) {
                std::cout << "Congratulations! You reached 2048!" << std::endl;
            }
            
            if (grid->isGameOver()) {
                std::cout << "Game Over! Final Score: " << grid->getScore() << std::endl;
                std::cout << "Press R to restart" << std::endl;
            }
        }
    }
}

void Game::update() {
    // Future: Add animations, tile movements, etc.
}

void Game::render() {
    window->clear();
    
    // Render grid
    gridView->render();
    
    // TODO: Render score, game over text, etc.
    
    window->present();
}

void Game::cleanup() {
    // Window cleanup is handled by unique_ptr destructor
}