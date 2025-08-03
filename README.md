# ImGui_Ned_Embed
Add Ned to your Dear ImGui app!

## Prerequisites

Before building this project, you need to install the following dependencies:

### On macOS (using Homebrew):
```bash
brew install cmake glfw
```

### On Ubuntu/Debian:
```bash
sudo apt-get install cmake libglfw3-dev libgl1-mesa-dev
```

### On Windows:
- Install CMake from https://cmake.org/download/
- Install GLFW from https://www.glfw.org/download/
- Install a C++ compiler (Visual Studio, MinGW, etc.)

## Building the Project

1. Clone the repository and initialize submodules:
```bash
git clone <your-repo-url>
cd ImGui_Ned_Embed
git submodule update --init --recursive
```

2. Run the build script:
```bash
./build.sh
```

## Running the Demo

After successful build, run the demo:
```bash
./build/ImGuiDemo
```

## Features

The demo includes:
- ImGui demo window with all available widgets
- Custom window with interactive controls
- Real-time FPS counter
- Color picker and sliders
- Button interactions

## Project Structure

- `main.cpp` - Main application with ImGui demo
- `CMakeLists.txt` - CMake configuration
- `build.sh` - Build script
- `imgui/` - ImGui library (submodule)

## Troubleshooting

If you encounter build errors:
1. Make sure all dependencies are installed
2. Ensure you have a C++17 compatible compiler
3. Check that the ImGui submodule is properly initialized
