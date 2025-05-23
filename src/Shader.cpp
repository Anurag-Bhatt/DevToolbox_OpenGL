#include <glad/glad.h>
#include "Shader.hpp"
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);

    if(vertexFile && fragmentFile){

        std::stringstream vStream, fStream;

        vStream << vertexFile.rdbuf();
        fStream << fragmentFile.rdbuf();

        m_VShader = vStream.str();
        m_FShader = fStream.str();

        printShaders();
        compileShaders();

        attachProgram();

    }else{
        if(!vertexFile) std::cout << "Error opening file at : " << vertexPath << std::endl;
        if(!fragmentFile) std::cout << "Error opening file at: " << fragmentPath << std::endl; 
    }
}

Shader::~Shader()
{
}

void Shader::use() const
{
    glUseProgram(m_ProgramID);
}

unsigned int Shader::getProgram() const
{
    return m_ProgramID;
}

void Shader::printShaders()
{
    std::cout << "Vertex Shader \n" << m_VShader << std::endl;
    std::cout << "Fragment Shader \n" << m_FShader << std::endl;
}

void Shader::compileShaders()
{
    m_vShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char * vShaderSrc = m_VShader.c_str();
    glShaderSource(m_vShaderID, 1, &vShaderSrc, nullptr);
    glCompileShader(m_vShaderID);

    int success;
    char infoLog[512];

    glGetShaderiv(m_vShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_vShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    m_fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fShaderSrc = m_FShader.c_str();
    glShaderSource(m_fShaderID, 1, &fShaderSrc, nullptr);
    glCompileShader(m_fShaderID);

    glGetShaderiv(m_fShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_fShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::attachProgram()
{
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, m_vShaderID);
    glAttachShader(m_ProgramID, m_fShaderID);
    glLinkProgram(m_ProgramID);

    int success;
    char infoLog[512];
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(m_vShaderID);
    glDeleteShader(m_fShaderID);
}
