#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>

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


#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::vector<json> loadMaterial(std::filesystem::path materialPath);

void showMaterial(std::vector<json> &materials);

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

    float lightCirclingRadius = 1.0f;

    std::filesystem::path materialPath("../Material/Materials.json");
    std::vector<json> materials = loadMaterial(materialPath);

    while (window.shoulBeOpen()) {
        
        window.clearBuffer(bgColor); 
        window.beginUIFrame();
        
        
        // ImGui UI, for helping in debugging

        static float ambientStrength, specularStrength;
        static int shininess;

        lightModel = glm::mat4(1.0f);
        if(window.showUI){
            
            ImGui::Begin("Settings");

            ImGui::InputFloat("Ambience", &ambientStrength);
            ImGui::InputFloat("Specular Strength", &specularStrength);
            ImGui::InputInt("Shininess", &shininess);

            static bool showMats;
            if(ImGui::Button("Show Materials")){
                showMats =! showMats;
            }

            if(showMats){
                showMaterial(materials);
            }

            static int selectedMaterial;
            static std::vector<std::string> materialNames;
            materialNames.clear();
            for (const auto& mat : materials) {
                materialNames.push_back(mat["name"]);
            }

            ImGui::Combo("Material", &selectedMaterial,
                [](void* data, int idx, const char** out_text) {
                    auto& names = *static_cast<std::vector<std::string>*>(data);
                    if (idx < 0 || idx >= names.size()) return false;
                    *out_text = names[idx].c_str();
                    return true;
                },
                static_cast<void*>(&materialNames), materialNames.size()
            );

            ImGui::End();
        }

        glm::vec3 dynamicLightPos = glm::vec3(lightCirclingRadius * cos(glfwGetTime()), 0.0f, lightCirclingRadius * sin(glfwGetTime()));
        lightModel = glm::translate(lightModel, dynamicLightPos);
        lightSource.setTransform(dynamicLightPos);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);

        // Cube Shader and Cube Source
        cubeShader.use();
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPosition", lightSource.getPosition());
        cubeShader.setVec3("viewPosition", cam.getPosition());
        cubeShader.setMat4("view", cam.lookAt());
        cubeShader.setMat4("projection", projection);

        cubeShader.setFloat("ambientStrength", ambientStrength);
        cubeShader.setFloat("specularStrength", specularStrength);
        cubeShader.setInt("shininess", shininess);
        
        tex1.bind(0);
        tex2.bind(1);        
        
        cubeShader.setInt("texture1", 0);
        cubeShader.setInt("texture2", 1);
        
        glm::mat4 model = glm::mat4(1.0f);
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

std::vector<json> loadMaterial(std::filesystem::path materialPath)
{
    // TODO: insert return statement here
    std::vector<json> material;

    std::ifstream file(materialPath);
    json j;
    file >> j;

    return j.get<std::vector<json>>();
}

void showMaterial(std::vector<json> &materials)
{
    ImGui::Begin("Materials");

    for(auto& mat : materials){

        if(ImGui::CollapsingHeader(mat["name"].get<std::string>().c_str())){

            ImGui::Text("Ambient: %.3f, %.3f, %.3f", 
            mat["ambient"][0].get<float>(),
            mat["ambient"][1].get<float>(),
            mat["ambient"][2].get<float>());

            ImGui::Text("Diffusion: %.3f, %.3f, %.3f", 
            mat["diffuse"][0].get<float>(),
            mat["diffuse"][1].get<float>(),
            mat["diffuse"][2].get<float>());

            ImGui::Text("Specular: %.3f, %.3f, %.3f", 
            mat["specular"][0].get<float>(),
            mat["specular"][1].get<float>(),
            mat["specular"][2].get<float>());

            ImGui::Text("Shininess: %.3f", mat["shininess"].get<float>());
        }

    }

    ImGui::End();
}
