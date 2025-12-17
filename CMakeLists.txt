cmake_minimum_required(VERSION 3.15)

if(DEFINED ENV{PROJECT_NAME})
    set(APP_NAME $ENV{PROJECT_NAME})
else()
    set(APP_NAME "SDL2App")
endif()

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 -mwindows)
endif()

# Windows-specific settings
if(WIN32)
    # Hide console window for release builds
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )
    
    # Copy SDL2 DLL to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# Installation rules
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(FILES $<TARGET_FILE:SDL2::SDL2> DESTINATION . OPTIONAL)