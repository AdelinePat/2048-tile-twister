cmake_minimum_required(VERSION 3.15)

# Project name from environment (Docker)
if(DEFINED ENV{PROJECT_NAME})
    set(APP_NAME $ENV{PROJECT_NAME})
else()
    set(APP_NAME "SDL3App")
endif()

project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to build only tests (for Linux native testing)
option(BUILD_TESTS_ONLY "Build only the test executable" OFF)

# ==================================================
# Core library (NO SDL, NO GUI)
# ==================================================
add_library(${APP_NAME}_core STATIC
    src/core/tile.cpp
    src/core/grid.cpp
    src/core/game.cpp
)

target_include_directories(${APP_NAME}_core PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# ==================================================
# Tests (console-only, NO SDL, NO GUI)
# Only build tests if not cross-compiling for Windows
# ==================================================
if(NOT CMAKE_CROSSCOMPILING OR BUILD_TESTS_ONLY)
    add_executable(test
        tests/gameTest.cpp
        tests/gridTest.cpp
    )

    # Link to core library
    target_link_libraries(test PRIVATE ${APP_NAME}_core)

    # Include directories
    target_include_directories(test PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        /usr/local/include
    )

    # Make test executable a console app
    if(WIN32)
        set_target_properties(test PROPERTIES 
            WIN32_EXECUTABLE OFF
            LINK_FLAGS "-mconsole"
        )
    endif()
endif()

# If we're only building tests, stop here
if(BUILD_TESTS_ONLY)
    return()
endif()

# ==================================================
# SDL Application (GUI) - Only if not BUILD_TESTS_ONLY
# ==================================================
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(${APP_NAME}
    src/main.cpp
    src/views/window.cpp
    src/views/tileView.cpp
    src/views/gridView.cpp
    src/views/gameObject.cpp
)

target_link_libraries(${APP_NAME}
    PRIVATE
        ${APP_NAME}_core
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)

# Windows-specific app settings
if(WIN32)
    target_link_libraries(${APP_NAME} PRIVATE mingw32)
    set_target_properties(${APP_NAME} PROPERTIES WIN32_EXECUTABLE ON)

    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            /usr/x86_64-w64-mingw32/bin/SDL3.dll
            $<TARGET_FILE_DIR:${APP_NAME}>
    )

    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            /usr/x86_64-w64-mingw32/bin/SDL3_ttf.dll
            $<TARGET_FILE_DIR:${APP_NAME}>
    )
endif()

# ==================================================
# Install rules
# ==================================================
install(TARGETS ${APP_NAME} DESTINATION .)

if(WIN32)
    install(FILES
        /usr/x86_64-w64-mingw32/bin/SDL3.dll
        /usr/x86_64-w64-mingw32/bin/SDL3_ttf.dll
        DESTINATION .
        OPTIONAL
    )
endif()