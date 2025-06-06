#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;

class Camera {

public:
    
    Camera( glm::vec3 position = glm::vec3{0.0f, 0.0f, 3.0f}, glm::vec3 front = glm::vec3{0.0f, 0.0f, -1.0f}, 
            glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f}, float yaw = YAW, float pitch = PITCH );
    ~Camera();

    void processKeyboardInput(GLFWwindow *window, float deltaTime);
    void processMouseInput(GLFWwindow* window);

    glm::mat4 lookAt();
    glm::mat4 perspective(float aspectRatio);

    bool firstMouse = true;

private:

    void updateCameraVectors();

    // Camera Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    // Angles    
    float m_yawAngle;
    float m_pitchAngle;
    
    // Camera Movements
    float m_movementSpeed; 
    float m_senstivity;

};