cmake_minimum_required(VERSION 3.20)
project(Game2048 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

# Source files
set(SOURCES
        src/main.cpp
        src/Window.cpp
        src/GameObject.cpp
        src/Tile.cpp
        src/TileView.cpp
        src/Grid.cpp
        src/GridView.cpp
        src/Game.cpp
)

# Header files
set(HEADERS
        include/Window.hpp
        include/GameObject.hpp
        include/Tile.hpp
        include/TileView.hpp
        include/Grid.hpp
        include/GridView.hpp
        include/Game.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)