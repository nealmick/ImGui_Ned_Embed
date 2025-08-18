cmake_minimum_required(VERSION 3.16)
project(ImGuiDemo)

# Set NED path - can be customized for different setups
set(NED_PATH "ned" CACHE PATH "Path to the NED project")

# Speed up build by disabling non-essential features for demo
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libs for faster linking")
set(BUILD_TESTS OFF CACHE BOOL "Skip tests for faster build")
set(USE_SSH OFF CACHE BOOL "Disable SSH for faster build")
# Skip building standalone ned executable - we only need ned_embed
set(CMAKE_DISABLE_FIND_PACKAGE_PkgConfig TRUE CACHE BOOL "Disable pkg-config")

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

# Add include directories that ned_embed needs
target_include_directories(ImGuiDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/lib/utfcpp/source
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Link with NED
target_link_libraries(ImGuiDemo ned_embed)

# Add Windows-specific libraries for ned_embed
if(WIN32)
  target_link_libraries(ImGuiDemo 
    winhttp
    secur32
    crypt32
    rpcrt4
    ws2_32
    advapi32
    shell32
    ole32
    oleaut32
    user32
    comdlg32
  )
endif()

# Copy resources to build directory so the demo can find icons and assets
file(COPY 
  ${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/icons
  ${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/fonts
  ${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/settings
  ${CMAKE_CURRENT_SOURCE_DIR}/${NED_PATH}/shaders
  DESTINATION ${CMAKE_BINARY_DIR}/Release
)