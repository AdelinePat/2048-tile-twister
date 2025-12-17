cmake_minimum_required(VERSION 3.10)
project(HelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Inclure SDL3
include_directories(${CMAKE_SOURCE_DIR}/SDL3/include)

# Lier SDL3 (libs VC)
link_directories(${CMAKE_SOURCE_DIR}/SDL3/lib/x64)

add_executable(HelloWorld    
    src/main.cpp
    src/Tile.cpp
    src/Grid.cpp
    src/Window.cpp
    src/Game.cpp
)

# Lier SDL3
target_link_libraries(HelloWorld
    SDL3
)
