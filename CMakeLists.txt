cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)

# Add ImGui as a submodule (or use system ImGui)
add_subdirectory(imgui)

# Add NED as subdirectory
# You can switch between:
# - Local path: add_subdirectory(../ned ned)
# - Submodule path: add_subdirectory(ned)
# - Any other path: add_subdirectory(/path/to/ned ned)
#add_subdirectory(../ned ned)
#add_subdirectory(ned)

add_executable(ImGuiDemo main.cpp)

# Link everything together
# (Order: OpenGL, glfw, GLEW, Freetype, imgui, ned_embed)
target_link_libraries(ImGuiDemo
    OpenGL::GL
    glfw
    GLEW::GLEW
    Freetype::Freetype
    imgui
    ned_embed
) 