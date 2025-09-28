// GLEW must be included before any other OpenGL headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ned_embed.h"

// Include this for custom texture manager implementations
#include "util/texture_manager.h"
#include <iostream>

// Example custom texture manager implementation
// This demonstrates how to create your own texture manager for integration
// with different rendering backends (OpenGL, Vulkan, DirectX, Unreal, etc.)
class CustomOpenGLTextureManager : public ITextureManager
{
public:
    ImTextureID createTexture(const unsigned char* pixels, int width, int height) override
    {
        std::cout << "[CustomTextureManager] Creating texture " << width << "x" << height << std::endl;

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        return static_cast<ImTextureID>(texture);
    }

    void destroyTexture(ImTextureID textureId) override
    {
        if (textureId) {
            std::cout << "[CustomTextureManager] Destroying texture" << std::endl;
            GLuint texture = static_cast<GLuint>(textureId);
            glDeleteTextures(1, &texture);
        }
    }

    bool getTextureDimensions(ImTextureID textureId, int& width, int& height) override
    {
        if (!textureId) return false;

        GLuint texture = static_cast<GLuint>(textureId);
        GLint previousTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

        // Restore previous texture
        glBindTexture(GL_TEXTURE_2D, previousTexture);

        return true;
    }
};

int main() {
    // Create window
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "NED Editor Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Initialize GLEW before using any OpenGL functions
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    // Setup ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");
    
    // Initialize NED editor (auto-initialized in constructor)
    // Option 1: Use default OpenGL texture manager (current behavior)
    // NedEmbed nedEditor;

    // Option 2: Use custom texture manager (for integration with other engines)
    // Create your custom texture manager (e.g., UnrealTextureManager, VulkanTextureManager, etc.)
    CustomOpenGLTextureManager customTextureManager;

    // Configure NED embed options
    NedEmbedOptions options;
    options.textureManager = &customTextureManager;
    // Option to bypass native file dialog project picker, and set project here.
    options.projectPath = "/Users/neal/dev/ned";
    // Create NED editor with custom options
    NedEmbed nedEditor(options);

        // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        // Check for font reloading BEFORE ImGui frame starts
        nedEditor.checkForFontReload();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Show ImGui demo window
        ImGui::ShowDemoWindow();
        
        // Show NED editor window
        ImGui::SetNextWindowSize(ImVec2(1200, 800), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("NED Editor", nullptr, 0)) {
            nedEditor.render();
        }
        ImGui::End();
        
        // Render
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    nedEditor.cleanup();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 