#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "WindowManager.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Color bgColor = {0.2f, 0.3f, 0.3f, 1.0f};

int main() {

    WindowManager window(SCREEN_WIDTH,SCREEN_HEIGHT, std::string("Raytracer"));
        
    while (window.shoulBeOpen()) {
        window.pollEvents();
        
        window.beginUIFrame();

        // Your ImGui UI
        if(window.showUI){
        ImGui::Begin("Controls");
        ImGui::Text("Welcome to your Raytracer");
        ImGui::End();
        }

        window.renderUI(bgColor);

        window.swapBuffers();
    }

    return 0;
}
