#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

#include "imgui.h"

#include "WindowManager.hpp"
#include "Shader.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Color bgColor = {0.2f, 0.3f, 0.3f, 1.0f};

/*
    (DONE)Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data: 
    solution.
    
    (Done)Now create the same 2 triangles using two different VAOs and VBOs for their data: solution.
    
    (Done)Create two shader programs where the second program uses a different fragment shader that outputs 
    the color yellow; draw both triangles again where one outputs the color yellow: solution.

*/

int main() {

    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    WindowManager window(SCREEN_WIDTH,SCREEN_HEIGHT, std::string("Raytracer"));
    
    Shader myShader("../shaders/screen.vert", "../shaders/raytrace.frag");

    
    float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f  // top left 
    }; 

    float vertices2ndTriangle[] = {
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    // Generating and binding buffer to vertex data
    unsigned int VBOs[2], VAOs[2], EBO;

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Triangle 1 setup
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Triangle 2 setup
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2ndTriangle), vertices2ndTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, 1);
    // glBindVertexArray(1);

    while (window.shoulBeOpen()) {
        window.pollEvents();

        window.clearBuffer(bgColor);

        myShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        myShader.use();
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
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
