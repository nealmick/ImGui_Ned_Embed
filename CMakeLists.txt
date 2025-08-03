cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Find GLEW
find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew)

# Add the NED project as a subdirectory (using local directory)
add_subdirectory(../ned ned)

# Create the main demo executable
add_executable(ImGuiDemo main.cpp
)

target_include_directories(ImGuiDemo PRIVATE 
    ${GLEW_INCLUDE_DIR}
    ned  # Include NED headers
)

target_link_libraries(ImGuiDemo 
    OpenGL::GL 
    glfw 
    ${GLEW_LIBRARY}
    ned_embed  # Link against the NED embeddable library
) 