#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <cmath>

#include "imgui.h"

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Color bgColor = {0.2f, 0.3f, 0.3f, 1.0f};

int main() {

    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    WindowManager window(SCREEN_WIDTH,SCREEN_HEIGHT, std::string("Raytracer"));
    
    Shader myShader("../shaders/screen.vert", "../shaders/raytrace.frag");

    std::vector<float> triangle1 = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f  // top left 
    }; 

    std::vector<float> triangle2 = {
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<float> vertices = {
    // x,    y,     z           // colors       texture coords
     0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,      // 0: top right
     0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,      // 1: bottom right
    -0.5f, -0.5f,  0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,      // 2: bottom left
    -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f       // 3: top left
    };

    std::vector<unsigned int> indices = {  
        // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    Mesh mesh1(triangle1);
    Mesh mesh2(triangle2);

    Mesh quad(vertices, indices);
    quad.setLayout({3, 3, 2});

    Texture tex1("../assets/images/container.jpg");
    Texture tex2("../assets/images/awesomeface.png");


    while (window.shoulBeOpen()) {
        
        window.pollEvents();
        window.clearBuffer(bgColor); 
        window.beginUIFrame();
        
        // Your ImGui UI
        if(window.showUI){
            ImGui::Begin("Settings");
            ImGui::Text("Welcome to your Raytracer");
            
            static bool buttonPressed = false;
            if(ImGui::Button("Render a Quad")){
                buttonPressed = !buttonPressed;
            }

            if(buttonPressed)
            {

                myShader.use();
                tex1.bind();
                myShader.setInt("texture2", 0);
                tex2.bind(1);
                myShader.setInt("texture2", 1);

                static float mixParameter;
                ImGui::InputFloat("Mix Parameter", &mixParameter, 0.01, 0.1);
                myShader.setFloat("mixParameter", mixParameter);
                quad.bind();
                quad.draw();
            }

            ImGui::End();
        }
        
        window.renderUI(bgColor);

        window.swapBuffers();
    }

    return 0;
}
