#include <iostream>
#include <glad/glad.h>
#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> &vertices)
: m_vertexCount(vertices.size()), m_EBO(0), m_layout(0)
{
    std::cout << "Vertices size: " << vertices.size() << "\n";
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    // Vertex Bind Buffer Objects
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data() , GL_STATIC_DRAW);

}

Mesh::Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices)
: m_indexCount(indices.size()), m_EBO(0), m_layout(0)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    
    // Vertex Bind Buffer Objects
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Bind Element Buffer Objects
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

}

Mesh::~Mesh()
{
    unbind();
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
    if(m_EBO){
        glDeleteBuffers(1, &m_EBO);
    }
}

Mesh::Mesh(Mesh &&other) noexcept
{
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;
    m_EBO = other.m_EBO;

    m_vertexCount = other.m_vertexCount;
    m_indexCount = other.m_indexCount;
    m_layout = other.m_layout;
    m_stride = other.m_stride;

    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;
}

Mesh &Mesh::operator=(Mesh &&other) noexcept
{
    // TODO: insert return statement here
    if(this != &other){

        glDeleteBuffers(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        if(m_EBO) glDeleteBuffers(1, &m_EBO);

        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_EBO = other.m_EBO;

        m_vertexCount = other.m_vertexCount;
        m_indexCount = other.m_indexCount;
        m_layout = other.m_layout;
        m_stride = other.m_stride;

        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_EBO = 0; 
    }

    return *this;

}

void Mesh::bind() const
{
    glBindVertexArray(m_VAO);
}
void Mesh::unbind() const
{
    glBindVertexArray(0);
}

void Mesh::draw() const
{
    bind();
    if(m_EBO == 0){
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertexCount));
        
    }else{
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, 0);
    }
    unbind();
}

void Mesh::setLayout(const std::vector<unsigned int> layout)
{
    m_layout = layout;
    for(auto count : m_layout){
        m_stride += count;
    }

    m_vertexCount /= m_stride;

    std::cout << "Stride: " << m_stride <<", Vertex Count: " << m_vertexCount << "\n";

    m_stride *=  sizeof(float);

    bind();
    setupAttribs();
    unbind();
}

void Mesh::setupAttribs()
{
    size_t offset = 0;
    for(unsigned int i = 0; i < m_layout.size(); i++){
    
        glVertexAttribPointer(i, m_layout[i], GL_FLOAT, GL_FALSE, m_stride, (void*)(offset*sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += m_layout[i];
    }
}
