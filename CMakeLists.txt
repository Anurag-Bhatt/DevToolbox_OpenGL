cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME OpenGLAPP)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# Enable new policy for GLVND
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# ImGui sources
set(IMGUI_SOURCES
    src/ImGui/imgui.cpp
    src/ImGui/imgui_draw.cpp
    src/ImGui/imgui_widgets.cpp
    src/ImGui/imgui_tables.cpp
    src/ImGui/backend/imgui_impl_glfw.cpp
    src/ImGui/backend/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    include/ImGui
    include/ImGui/backend
)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add main executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/WindowManager.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/Object.cpp
)

# Include main include dir
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link all dependencies
target_link_libraries(${PROJECT_NAME}
    imgui
    glfw
    OpenGL::GL
    dl # required on Linux for glad
)
