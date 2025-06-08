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
    
    std::vector<float> vertices = {
            // position         // uv
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 8
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 9
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 10
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 11

         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 12
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 13
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 14 
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 15

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 16
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 17
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 19

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 20
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 21
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 22
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // 23
    };

    std::vector<unsigned int> indices = {
        // back face
        0, 1, 2, 2, 3, 0,
        // front face
        4, 5, 6, 6, 7, 4,
        // left face
        8, 9,10,10,11, 8,
        // right face
        12,13,14,14,15,12,
        // bottom face
        16,17,18,18,19,16,
        // top face
        20,21,22,22,23,20
    };


    std::vector<float> lightCubeVertices = {
            // position         // uv
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3

        -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f, // 7

        -0.5f,  0.5f,  0.5f, // 8
        -0.5f,  0.5f, -0.5f, // 9
        -0.5f, -0.5f, -0.5f, // 10
        -0.5f, -0.5f,  0.5f, // 11

         0.5f,  0.5f,  0.5f, // 12
         0.5f,  0.5f, -0.5f, // 13
         0.5f, -0.5f, -0.5f, // 14
         0.5f, -0.5f,  0.5f, // 15

        -0.5f, -0.5f, -0.5f, // 16
         0.5f, -0.5f, -0.5f, // 17
         0.5f, -0.5f,  0.5f, // 18
        -0.5f, -0.5f,  0.5f, // 19

        -0.5f,  0.5f, -0.5f, // 20
         0.5f,  0.5f, -0.5f, // 21
         0.5f,  0.5f,  0.5f, // 22
        -0.5f,  0.5f,  0.5f, // 23
    };

    std::vector<unsigned int> lightCubeIndices = {
        // back face
        0, 1, 2, 2, 3, 0,
        // front face
        4, 5, 6, 6, 7, 4,
        // left face
        8, 9,10,10,11, 8,
        // right face
        12,13,14,14,15,12,
        // bottom face
        16,17,18,18,19,16,
        // top face
        20,21,22,22,23,20
    };


    Texture tex1("../assets/images/container.jpg");
    Texture tex2("../assets/images/awesomeface.png");
 
    Shader myShader("../shaders/screen.vert", "../shaders/raytrace.frag");
    Shader lightShader("../shaders/lightSource.vert", "../shaders/lightSource.frag");

    auto sharedCubeMesh = std::make_shared<Mesh>(vertices, indices);
    sharedCubeMesh->setLayout({3, 2});

    Object cube(sharedCubeMesh);
    cube.setTransform(glm::vec3(0.0,0.0,0.0));

    // TODO: work on light

    auto shareLightMesh = std::make_shared<Mesh>(lightCubeVertices, lightCubeIndices);
    shareLightMesh->setLayout({3});

    Object lightSource(shareLightMesh);
    lightSource.setTransform(glm::vec3(0.0, 4.0, 0.0));

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
        myShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        myShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        
        myShader.setMat4("view", cam.lookAt());
        myShader.setMat4("projection", glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f));
        tex1.bind(0);
        tex2.bind(1);        
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);
        model = glm::translate(model, cube.getPosition());
        myShader.setMat4("model", model);
        cube.draw();

        tex1.unbind();
        tex2.unbind();

        lightShader.use();
        lightShader.setMat4("view", cam.lookAt());
        lightShader.setMat4("projection",glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f));
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel,lightSource.getPosition());
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lightShader.setMat4("model", lightModel);

        lightSource.draw();


        window.renderUI();
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
