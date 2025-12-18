#include "Game.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;
    
    if (!game.init()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }
    
    std::cout << "=== 2048 Game ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys or WASD - Move tiles" << std::endl;
    std::cout << "  R - Restart game" << std::endl;
    std::cout << "  ESC - Quit" << std::endl;
    std::cout << std::endl;
    
    game.run();
    game.cleanup();
    
    return 0;
}