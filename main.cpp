#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ned_embed.h"

int main() {
    // Create window
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "NED Editor Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    // Setup ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");
    
    // Initialize NED editor (auto-initialized in constructor)
    NedEmbed nedEditor;

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