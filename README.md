# ImGui NED Embed Demo

A demonstration of embedding the NED text editor as an ImGui window.

## Current State

✅ **Successfully implemented unified ImGui setup with git submodules**

### Project Structure
```
ImGui_Ned_Embed/
├── ned/           # NED editor as git submodule
├── imgui/         # ImGui library as git submodule  
├── main.cpp       # Demo application entry point
├── CMakeLists.txt # Build configuration
└── README.md      # This file
```

### How the CMake Works

The demo uses a **unified ImGui approach** to avoid conflicts between multiple ImGui installations:

1. **Unified ImGui Library**: Creates `imgui_unified` static library from the top-level `imgui` submodule
2. **NED Configuration**: Uses NED's custom ImGui configuration (`ned/ned_imgui_config.h`) for consistency
3. **Conditional Compilation**: NED's CMakeLists.txt detects if it's built as a subdirectory (embedded mode) vs standalone
4. **Clean Dependencies**: Uses standard `find_package()` calls for all dependencies

#### Key CMake Features:
- **Portable**: Works on macOS, Linux, Windows
- **Simple**: Only 58 lines of CMake configuration
- **Standard**: Uses `find_package()` for all dependencies (OpenGL, glfw3, Freetype, GLEW)
- **Unified**: Single ImGui library shared across the entire project

### Submodules

- **`ned/`**: The NED text editor project (git submodule)
- **`imgui/`**: Dear ImGui library (git submodule)

Both submodules are pinned to specific commits to ensure compatibility.

### Building

```bash
./build.sh
```

The build script:
1. Creates a `build/` directory
2. Configures with CMake
3. Builds the demo executable
4. Runs the demo

### Demo Features

- ✅ Embedded NED editor window
- ✅ Font loading and configuration
- ✅ Settings management
- ✅ ImGui demo window
- ✅ Proper resource path resolution

## Future Simplification Plans

### 🎯 **Goal: Make this the simplest possible ImGui embedding example**

#### Current Complexity Analysis:
- **Good**: Unified ImGui library prevents conflicts
- **Good**: Standard CMake `find_package()` usage
- **Good**: Clean submodule structure
- **Could Improve**: Still requires understanding of NED's internal structure

#### Potential Simplifications:

1. **Extract Core Embedding Logic**: 
   - Create a minimal `NedEmbed` wrapper that only exposes essential editor functionality
   - Hide complex features (LSP, AI, file tree) behind optional flags

2. **Simplify Resource Management**:
   - Bundle essential fonts/settings with the demo
   - Remove dependency on NED's complex resource path resolution

3. **Create Template Project**:
   - Make this a template that can be easily copied and modified
   - Add clear documentation for each CMake section

4. **Reduce Dependencies**:
   - Make LSP, AI, and advanced features optional
   - Create a "minimal" build mode

#### Ideal End State:
```cmake
# As simple as possible
cmake_minimum_required(VERSION 3.16)
project(MyImGuiApp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(ned)
add_executable(MyApp main.cpp)
target_link_libraries(MyApp ned_embed glfw OpenGL::GL)
```

## Technical Notes

### Why Unified ImGui?
NED uses a custom ImGui configuration (`IMGUI_USE_WCHAR32`) that differs from the default. The unified approach ensures:
- No symbol conflicts
- Consistent behavior between standalone and embedded modes
- Single source of truth for ImGui version

### Resource Path Resolution
The demo correctly resolves resources from the NED submodule, ensuring fonts and settings load properly in the embedded environment.

### Font Loading
Uses NED's font loading system with FreeType support, providing high-quality text rendering in the embedded editor.
