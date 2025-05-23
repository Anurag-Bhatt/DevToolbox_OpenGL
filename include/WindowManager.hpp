#pragma once
#include <string>
#include <GLFW/glfw3.h>

struct Color{
    float r;
    float g;
    float b;
    float a;
};


class WindowManager{

public:

    WindowManager(const int screenWidth, const int screenHeight, std::string windowTitle);
    ~WindowManager();

    bool shoulBeOpen() const;
    void swapBuffers() const;
    void pollEvents() const;
    void clearBuffer(Color&) const;

    bool showUI = true;
    void beginUIFrame() const;
    void renderUI(Color &bgColor) const;

    GLFWwindow* getWindow();

private:

    GLFWwindow* m_window;
    int m_width;
    int m_height;

    std::string m_title;
    bool isFullscreen;

    void init();
    void initImGui();
    void cleanUp();
    void shutDownImGui();

    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleKeyInput(int key, int scancode, int action, int mods); // instance method
};