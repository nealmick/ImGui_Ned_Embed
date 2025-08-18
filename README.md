# ImGui NED Embed Demo

A demonstration of embedding the NED text editor into an ImGui application. This project shows how to integrate NED's editor functionality into your own ImGui-based applications.

## Features

- Embedded NED text editor with full functionality
- ImGui-based user interface
- Tree Sitter syntax highlighting
- LSP integration support
- Terminal emulator
- Multi-cursor editing



https://github.com/user-attachments/assets/9998895d-d168-48e0-bd45-9dd7062a1b79




### System Requirements
- CMake (version 3.16 or higher)
- C++17 compatible compiler
- OpenGL
- GLFW3
- GLEW
- CURL
- FreeType

### Package Installation

#### macOS (Intel and ARM)
```bash
brew install clang-format cmake llvm glfw glew pkg-config curl freetype
```

#### Ubuntu/Debian
```bash
sudo apt install cmake libglfw3-dev libglew-dev libgtk-3-dev pkg-config build-essential libcurl4-openssl-dev clang-format mesa-utils libfreetype6-dev
```

#### Windows
The dependencies are managed by the build script

## Getting Started

### 1. Clone the Repository

Clone this repository with all submodules:

```bash
git clone --recursive https://github.com/nealmick/ImGui_Ned_Embed.git
cd ImGui_Ned_Embed
```
**Important**: This project uses submodules for both ImGui and NED. Make sure to clone the repo them recursively.

### 2. Initialize Submodules

```bash
# Initialize all submodules
git submodule init

```

### 3. Update NED to Latest Version

The NED submodule is configured to track the `main` branch. To get the latest features and bug fixes:

```bash
# Update NED submodule to latest commit on main branch
git submodule update --remote ned
```


### 4. Build the Project

#### macOS/Linux
Run the build script:
```bash
./build.sh
```

#### Windows
For Windows users run the automated build script using powershell:

```bash
./build-win.bat
# This may take 10-20 minutes as it requires Visual Studio
```

### 5. Run the Demo

#### Windows
The demo launches automatically after building with `build-win.bat`. To run it manually:

```bash
cd build/Release
ImGuiDemo.exe
```

#### macOS/Linux
```bash
./ImGuiDemo
```

## Project Structure

```
ImGui_Ned_Embed/
├── imgui/              # ImGui library submodule
├── ned/                # NED editor submodule
├── main.cpp            # Main application entry point
├── CMakeLists.txt      # Build configuration
├── build.sh            # Build script
├── build-win.bat       # Build script
```

## Submodules

This project uses two main submodules:

1. **ImGui** (`imgui/`): The official ImGui library from the docking branch
2. **NED** (`ned/`): The NED text editor project with all its dependencies


The NED editor is embedded through the `ned_embed` library, which provides a API for integration.

### Customization

You can customize the ImGui configuration by modifying the `ned_imgui_config.h` file in the NED submodule, or by creating your own configuration file.

## License

This project uses components with different licenses:
- ImGui: MIT License
- NED: MIT License
- Various tree-sitter parsers: MIT License

Please refer to the individual component licenses for more details.
