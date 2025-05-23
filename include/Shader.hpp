#pragma once

#include <string>
#include <iostream>

class Shader{

public:

    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void use() const;
    unsigned int getProgram() const;

    void setBool(const std::string &name, bool value)const;
    void setInt(const std::string &name, int value)const;
    void setFloat(const std::string &name, float value)const;

private:

    void printShaders();
    void compileShaders();
    void attachProgram();


    std::string m_VShader, m_FShader;
    unsigned int m_vShaderID, m_fShaderID;
    unsigned int m_ProgramID;

};