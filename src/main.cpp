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
#include "Object.hpp"

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

    WindowManager window(SCREEN_WIDTH, SCREEN_HEIGHT, std::string("Raytracer"));
    
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

    Texture tex1("../assets/images/container.jpg");
    Texture tex2("../assets/images/awesomeface.png");
 
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

    auto sharedCubeMesh = std::make_shared<Mesh>(cubeVertices);
    sharedCubeMesh->setLayout({3, 2});

    std::vector<Object> objects;
    for(auto p : cubePositions){
        Object newObject(sharedCubeMesh);
        newObject.setTransform(p);
        objects.emplace_back(newObject);
    }

    // Mesh quad(cubeVertices);
    
    Object cube(cubeVertices);
    cube.setLayout({3, 2});

    Camera cam;
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0,0.0,0.0));

    while (window.shoulBeOpen()) {
        
        // std::cout << window.getDeltaTime() << " is the deltaTime\n";
        //window.processInput();
        window.clearBuffer(bgColor); 
        window.beginUIFrame();
        cam.processKeyboardInput(window.getWindow(), window.getDeltaTime());
        cam.processMouseInput(window.getWindow());
        
        
        myShader.use();
        myShader.setMat4("view", cam.lookAt());
        myShader.setMat4("projection", glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f));
        
        tex1.bind(0);
        tex2.bind(1);
        
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);
        
        for(auto &obj : objects){

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, obj.getPosition());

            myShader.setMat4("model", model);
            obj.draw();
        }


        // for(unsigned int i = 0; i < cubePositions.size(); i++){
    
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
            
        //     myShader.setMat4("model", model);
        //     cube.draw();
        // }

        
        // myShader.setMat4("model", model);
        // cube.draw();

        window.renderUI();
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
