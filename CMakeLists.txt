cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Find GLEW
find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew)

# Add the NED project as a subdirectory (using git submodule)
# dev: add_subdirectory(../ned ned)
add_subdirectory(ned)

# Create the main demo executable
add_executable(ImGuiDemo main.cpp
)

target_include_directories(ImGuiDemo PRIVATE 
    imgui 
    imgui/backends 
    ${GLEW_INCLUDE_DIR}
    ned  # Include NED headers (updated path)
)

# Override the ned_embed target to use our imgui instead of its own
target_include_directories(ned_embed PRIVATE 
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_link_libraries(ImGuiDemo 
    OpenGL::GL 
    glfw 
    ${GLEW_LIBRARY}
    ned_embed  # Link against the NED embeddable library
) 