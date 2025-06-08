#pragma once

#include <string>
#include <iostream>

// GLM = OpenGL Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{

public:

    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void use() const;
    unsigned int getProgram() const;

    void setBool(const std::string &name, bool value)const;
    void setInt(const std::string &name, int value)const;
    void setFloat(const std::string &name, float value)const;
    void setVec3(const std::string &name, float x, float y, float z)const;
    void setMat4(const std::string &name, glm::mat4 trans)const;

private:

    void printShaders();
    void compileShaders();
    void attachProgram();


    std::string m_VShader, m_FShader;
    unsigned int m_vShaderID, m_fShaderID;
    unsigned int m_ProgramID;

};