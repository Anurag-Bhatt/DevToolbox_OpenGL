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

    WindowManager window(SCREEN_WIDTH, SCREEN_HEIGHT, std::string("I dont know"));
    
    std::vector<float> cubeVertices = {
    // positions           // uvs     // normals (back face)
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f,  0.0f, -1.0f, // 0
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f,  0.0f, -1.0f, // 1
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // 2
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  0.0f, -1.0f, // 3

    // front face
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  0.0f,  1.0f, // 4
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  0.0f,  1.0f, // 5
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // 6
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,  0.0f,  1.0f, // 7

    // left face
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // 8
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // 9
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //10
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  -1.0f,  0.0f,  0.0f, //11

    // right face
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f,  0.0f,  0.0f, //12
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f,  0.0f,  0.0f, //13
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f,  0.0f,  0.0f, //14
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f,  0.0f,  0.0f, //15

    // bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f,  0.0f, //16
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   0.0f, -1.0f,  0.0f, //17
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f,  0.0f, //18
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, -1.0f,  0.0f, //19

    // top face
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  1.0f,  0.0f, //20
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  1.0f,  0.0f, //21
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  1.0f,  0.0f, //22
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  1.0f,  0.0f  //23
};


    std::vector<unsigned int> cubeIndices = {
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
 
    Shader cubeShader("../shaders/screen.vert", "../shaders/raytrace.frag");
    Shader lightShader("../shaders/lightSource.vert", "../shaders/lightSource.frag");

    auto sharedCubeMesh = std::make_shared<Mesh>(cubeVertices, cubeIndices);
    sharedCubeMesh->setLayout({3, 2, 3});

    Object cube(sharedCubeMesh);
    cube.setTransform(glm::vec3(0.0,0.0,0.0));


    auto shareLightMesh = std::make_shared<Mesh>(lightCubeVertices, lightCubeIndices);
    shareLightMesh->setLayout({3});

    Object lightSource(shareLightMesh);
    lightSource.setTransform(glm::vec3(0.0, 4.0, 0.0));

    Camera cam;
    

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0,0.0,0.0));

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel,lightSource.getPosition());

    while (window.shoulBeOpen()) {
        
        window.clearBuffer(bgColor); 
        window.beginUIFrame();
        
        
        // ImGui UI, for helping in debugging
        if(window.showUI){
            static float lightPosition[3] = { 0.0f, 1.0f, 0.0f }; // default value
            ImGui::InputFloat3("Light Position", lightPosition);

            // Reset to identity before applying the translation
            lightModel = glm::mat4(1.0f);
            lightModel = glm::translate(lightModel, glm::vec3(lightPosition[0], lightPosition[1], lightPosition[2]));
        }

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);

        // Cube Shader and Cube Source
        cubeShader.use();
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPosition", lightSource.getPosition());
        cubeShader.setVec3("viewPosition", cam.getPosition());
        cubeShader.setMat4("view", cam.lookAt());
        cubeShader.setMat4("projection", projection);
        
        tex1.bind(0);
        tex2.bind(1);        
        
        cubeShader.setInt("texture1", 0);
        cubeShader.setInt("texture2", 1);
        
        model = glm::translate(model, cube.getPosition());
        cubeShader.setMat4("model", model);
        cube.draw();

        tex1.unbind();
        tex2.unbind();

        // Light source and Light Shader
        lightShader.use();
        
        lightShader.setMat4("view", cam.lookAt());
        lightShader.setMat4("projection", projection);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lightShader.setMat4("model", lightModel);

        lightSource.draw();


        window.renderUI();
        window.pollEvents();

        // Processing Camera Input
        cam.processKeyboardInput(window.getWindow(), window.getDeltaTime());
        cam.mouseControlEnabled = window.toggleMouseControl;
        cam.processMouseInput(window.getWindow());

        window.swapBuffers();
    }

    return 0;
}
