#include <iostream>
#include <glad/glad.h>

#include <Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool Camera::mouseControlEnabled = true;

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch)
:   m_position(position), m_front(front), m_up(up), m_yawAngle(yaw), m_pitchAngle(pitch),
    m_movementSpeed(SPEED), m_senstivity(SENSITIVITY), m_worldUp(up)
{
    
    updateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4 Camera::lookAt()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::perspective(float aspectRatio)
{
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);;
}

glm::vec3 Camera::getPosition() const
{
    return m_position;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
    front.y = sin(glm::radians(m_pitchAngle));
    front.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
    m_front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::processKeyboardInput(GLFWwindow* window,float deltaTime){

    // Keyboard Camera Input
    float cameraSpeed = m_movementSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        m_position += cameraSpeed * m_front;
        //std::cout << "W pressed \n";
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        m_position -= cameraSpeed * m_front;
        // std::cout << "S pressed \n";
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
        // std::cout << "A pressed \n";
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        m_position += glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
        // std::cout << "D pressed \n";
    }

}

void Camera::processMouseInput(GLFWwindow* window)
{
    // Mouse Input
    float yoffset, xoffset;

    if(mouseControlEnabled){

        double xMousePosition, yMousePosition;
        glfwGetCursorPos(window, &xMousePosition, &yMousePosition);

        if (firstMouse) {
            mouseLastX = xMousePosition;
            mouseLastY = yMousePosition;
            firstMouse = false;
        }
  
            yoffset = mouseLastY - yMousePosition; 
            xoffset = xMousePosition - mouseLastX;
            mouseLastX = xMousePosition;
            mouseLastY = yMousePosition;

            xoffset *= m_senstivity;
            yoffset *= m_senstivity;

            m_yawAngle   += xoffset;
            m_pitchAngle += yoffset;

            if(m_pitchAngle > 89.0f)
                m_pitchAngle = 89.0f;
            if(m_pitchAngle < -89.0f)
                m_pitchAngle = -89.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
            direction.y = sin(glm::radians(m_pitchAngle));
            direction.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
            m_front = glm::normalize(direction);
        

            updateCameraVectors();
    }else if (!mouseControlEnabled && !firstMouse){
        firstMouse = true;
    }
    
}