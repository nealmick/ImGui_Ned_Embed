// Silence OpenGL deprecation warnings on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

// Include GLEW first to avoid conflicts
#include <GL/glew.h>

#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Include the embeddable NED editor
#include "ned_embed.h"

int main() {
    if (!glfwInit()) return -1;
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "NED Editor Demo", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { std::cerr << "Failed GLEW" << std::endl; glfwTerminate(); return -1; }
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");
    
    NedEmbed nedEditor;
    if (!nedEditor.initialize()) return -1;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        nedEditor.handleFontReload();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        static bool show_demo = true;
        ImGui::ShowDemoWindow(&show_demo);
        
        ImGui::SetNextWindowSize(ImVec2(1200, 800), ImGuiCond_FirstUseEver);
        static bool windowOpen = true;
        if (ImGui::Begin("NED Editor", &windowOpen, 0)) {
            nedEditor.render(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
        }
        ImGui::End();
        
        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    nedEditor.cleanup();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 