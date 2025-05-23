#include <iostream>
#include <glad/glad.h>
#include "WindowManager.hpp"

// ImGui Headers
#include "imgui.h"
#include "backend/imgui_impl_glfw.h"
#include "backend/imgui_impl_opengl3.h"


WindowManager::WindowManager(const int screenWidth, const int screenHeight, std::string windowTitle)
: m_width(screenWidth), m_height(screenHeight), m_title(windowTitle)
{
    init();

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, WindowManager::keyCallback); 

    initImGui();

}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(m_window);
    cleanUp();
    shutDownImGui();
}

bool WindowManager::shoulBeOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

void WindowManager::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void WindowManager::pollEvents() const
{
    glfwPollEvents();
}

void WindowManager::clearBuffer(Color &color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::beginUIFrame() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void WindowManager::renderUI(Color &bgColor) const
{
    ImGui::Render();
    clearBuffer(bgColor);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GLFWwindow *WindowManager::getWindow()
{
    return m_window;
}

void WindowManager::init()
{
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void WindowManager::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark(); // or Light/Classic

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void WindowManager::shutDownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void WindowManager::cleanUp()
{

    glfwTerminate();
}

void WindowManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    WindowManager *self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    if(self){
        self->handleKeyInput(key, scancode, action, mods);
    }
}

void WindowManager::handleKeyInput(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Escape pressed!, closing window\n";
        glfwSetWindowShouldClose(m_window, true);
    }

    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        std::cout << "W Key Pressed\n";
    }

    if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
        std::cout << "Tab pressed, toggling UI\n";
        showUI = !showUI;
    }


}
