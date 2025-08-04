cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

# Set NED path - can be customized for different setups
set(NED_PATH "ned" CACHE PATH "Path to the NED project")

# Add NED as subdirectory
add_subdirectory(${NED_PATH} ned)

# Include ImGui source files directly
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/misc/freetype/imgui_freetype.cpp
)

# Create the demo executable with ImGui sources
add_executable(ImGuiDemo main.cpp ${IMGUI_SOURCES})

# Use NED's ImGui configuration
target_compile_definitions(ImGuiDemo PRIVATE IMGUI_USER_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/ned_imgui_config.h")

# Add FreeType include directories for ImGui
# Note: FreeType is found but not as a CMake target, so we don't need to add include dirs
# The freetype headers are typically in standard system paths

# Link with NED
target_link_libraries(ImGuiDemo ned_embed)