#!/bin/bash

set -e

echo "Building for platform: ${TARGET_PLATFORM:-windows}"



# Create build directory
mkdir -p build
cd build

# Configure CMake based on platform
if [ "${TARGET_PLATFORM}" = "linux" ]; then
    echo "Configuring for Linux..."
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    
    # Create distribution directory
    mkdir -p /app/dist-linux
    cp $PROJECT_NAME /app/dist-linux/
    
    echo "✓ Linux build complete! Executable in dist-linux/ folder"
    echo "  Note: Linux executable requires SDL2 to be installed on target system:"
    echo "  sudo apt-get install libsdl2-2.0-0"
    
else
    echo "Configuring for Windows..."
    cmake -DCMAKE_TOOLCHAIN_FILE=/toolchain.cmake \
          -DCMAKE_BUILD_TYPE=Release ..
    make
    
    # Create distribution directory
    mkdir -p /app/dist-windows
    cp $PROJECT_NAME.exe /app/dist-windows/
    cp /usr/x86_64-w64-mingw32/bin/SDL2.dll /app/dist-windows/
    
    echo "✓ Windows build complete! Executable and DLL in dist-windows/ folder"
    echo "  Ready to run on Windows without any installation!"
fi