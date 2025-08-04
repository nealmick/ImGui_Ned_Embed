# NED Editor - ImGui Embed Demo

This project demonstrates how to embed the NED text editor into your own ImGui applications. It shows a complete working example of integrating NED as a component within an ImGui-based application.

## Project Structure

```
ImGui_Ned_Embed/
├── main.cpp              # Demo application entry point
├── CMakeLists.txt        # Build configuration
├── build.sh              # Build script
├── ned/                  # NED submodule (embedded editor)
├── imgui/                # ImGui submodule
└── README.md            # This file
```

## Features

- **Complete NED Editor**: Full-featured text editor with syntax highlighting, file tree, and AI agent
- **ImGui Integration**: Seamlessly embedded as an ImGui window
- **Font Management**: Dynamic font loading and size adjustment
- **Settings Integration**: Full settings system with embedded mode support
- **Simple API**: Easy to integrate into your own projects

## Building

### Prerequisites

- CMake 3.16+
- OpenGL
- GLFW3
- FreeType
- GLEW
- C++17 compiler

### Build Instructions

```bash
# Clone with submodules
git clone --recursive <repository-url>
cd ImGui_Ned_Embed

# Build
./build.sh

# Run
./ImGuiDemo
```

## Usage

The demo application shows:
- ImGui demo window (for reference)
- Embedded NED editor window
- Font size adjustment (Cmd++/Cmd+-)
- Settings window with embedded mode optimizations

## Integration Guide

### Basic Integration

```cpp
#include "ned_embed.h"

// Initialize
NedEmbed nedEditor;
nedEditor.initialize();

// In your render loop
nedEditor.checkForFontReload();  // Call BEFORE ImGui::NewFrame()
ImGui::NewFrame();

// Render the editor
if (ImGui::Begin("My Editor")) {
    nedEditor.render();
}
ImGui::End();

// Cleanup
nedEditor.cleanup();
```

### Key Integration Points

1. **Font Reloading**: Must call `checkForFontReload()` before `ImGui::NewFrame()`
2. **Embedded Mode**: Automatically configured for embedded use
3. **Settings**: Uses embedded-optimized settings (transparent scrollbars, etc.)
4. **Window Management**: Handles its own internal window management

## Configuration

### Switching Between Local and Submodule

The CMakeLists.txt supports multiple ways to include NED:

```cmake
# Use submodule (current)
add_subdirectory(ned)

# Use local path
add_subdirectory(../ned ned)

# Use any other path
add_subdirectory(/path/to/ned ned)
```

### Embedded Mode Features

When used as an embedded component, NED automatically:
- Disables window dragging from content area (only title bar)
- Makes settings window non-collapsible
- Uses transparent scrollbar tracks
- Optimizes background colors for embedded use
- Handles font reloading internally

## Architecture

### Unified ImGui Setup

The project uses a unified ImGui library approach:
- Single ImGui build from the `imgui/` submodule
- NED components link to the same ImGui library
- Prevents redefinition errors and version conflicts
- Uses NED's custom ImGui configuration

### Conditional Compilation

NED's CMakeLists.txt detects whether it's being built:
- **Standalone**: Compiles its own ImGui sources
- **Embedded**: Uses parent project's ImGui library

This allows NED to work both as a standalone application and as an embedded component.

## Troubleshooting

### Common Issues

1. **Font Reloading Crashes**: Ensure `checkForFontReload()` is called before `ImGui::NewFrame()`
2. **ImGui Redefinition**: The unified setup should prevent this
3. **Missing Dependencies**: Check that all required libraries are installed

### Build Issues

- **GLFW not found**: Install via package manager or build from source
- **FreeType not found**: Install development headers
- **OpenGL not found**: Ensure OpenGL development libraries are installed


## Contributing

When contributing to the embedded demo:
1. Test both local and submodule paths
2. Ensure font reloading works correctly
3. Verify embedded mode features function properly
4. Update this README for any new features

## License

See the main NED repository for license information.
