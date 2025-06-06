#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <random>

#include "imgui.h"

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

// GLM = OpenGL Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * Improve keyboard input and add mouse input.
*/

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Color bgColor = {0.2f, 0.3f, 0.3f, 1.0f};

int main() {

    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    WindowManager window(SCREEN_WIDTH,SCREEN_HEIGHT, std::string("Raytracer"));
    
    Shader myShader("../shaders/screen.vert", "../shaders/raytrace.frag");

    std::vector<float> cubeVertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<unsigned int> indices = {  
        // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    Mesh quad(cubeVertices);
    quad.setLayout({3, 2});

    Texture tex1("../assets/images/container.jpg");
    Texture tex2("../assets/images/awesomeface.png");
 
    glm::mat4 trans(1.0f);
    
    std::random_device rd;  // seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // range [0.0, 1.0)

    std::vector<glm::vec3> cubePositions = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);

    Camera cam;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    
    while (window.shoulBeOpen()) {
        
        std::cout << window.getDeltaTime() << " is the deltaTime\n";
        //window.processInput();
        window.clearBuffer(bgColor); 
        window.beginUIFrame();
        cam.processKeyboardInput(window.getWindow(), window.getDeltaTime());
        cam.processMouseInput(window.getWindow());
        
        // myShader.setMat4("model", model);
        // glm::mat4 view;
        // view = glm::lookAt(window.cameraPos, window.cameraPos + window.cameraFront, window.cameraUp);
        myShader.setMat4("view", cam.lookAt());
        myShader.setMat4("projection",projection);
        

        // Your ImGui UI
        myShader.use();
        // glm::mat4 rotate(1.0f);
        // model = glm::rotate(model, deltaTime * rotationSpeed *glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        tex1.bind();
        tex2.bind(1);
        
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);
        quad.bind();
        for(unsigned int i = 0; i < cubePositions.size(); i++){
    
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            // float angle = 20.0f * i * sin(glfwGetTime()); 
            // model = glm::rotate(model, rotationSpeed * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.setMat4("model", model);
            quad.draw();
        }
        // glDrawArrays(GL_TRIANGLES, 0, 36);
       
       
        window.renderUI();
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
