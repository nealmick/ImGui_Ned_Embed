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

## Getting Started

### 1. Clone the Repository

Clone this repository with all submodules:

```bash
git clone --recursive https://github.com/your-username/ImGui_Ned_Embed.git
cd ImGui_Ned_Embed
```

### 2. Initialize Submodules

**Important**: This project uses submodules for both ImGui and NED. Make sure to initialize them recursively:

```bash
# Initialize all submodules
git submodule init
git submodule update --init --recursive
```

**Note**: The `--recursive` flag is crucial because NED itself has its own submodules (tree-sitter parsers, etc.) that need to be initialized.

### 3. Update NED to Latest Version (Recommended)

The NED submodule is configured to track the `main` branch. To get the latest features and bug fixes:

```bash
# Update NED submodule to latest commit on main branch
git submodule update --remote ned

# Commit the updated submodule reference
git add ned
git commit -m "Update ned submodule to latest commit"
```

**Note**: This step is optional but recommended to get the latest NED features and improvements.

### 4. Build the Project

Run the build script:

```bash
./build.sh
```

This will:
- Configure the project with CMake
- Build the NED library and all its dependencies
- Compile the ImGui demo application
- Create the `ImGuiDemo` executable

### 5. Run the Demo

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
