cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)

# Create unified ImGui library from submodule
add_library(imgui_unified STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/misc/freetype/imgui_freetype.cpp
)

# Use NED's ImGui configuration
target_compile_definitions(imgui_unified PRIVATE
    IMGUI_USER_CONFIG="ned/ned_imgui_config.h"
)

target_include_directories(imgui_unified PUBLIC
    imgui
    imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}  # For finding ned/ned_imgui_config.h
)

target_link_libraries(imgui_unified PUBLIC
    Freetype::Freetype
    glfw
)

# Add NED as subdirectory
add_subdirectory(ned)

# Create demo executable
add_executable(ImGuiDemo main.cpp)

target_include_directories(ImGuiDemo PRIVATE 
    ned  # Include NED headers
)

target_link_libraries(ImGuiDemo 
    OpenGL::GL 
    glfw 
    GLEW::GLEW
    imgui_unified
    ned_embed
) 