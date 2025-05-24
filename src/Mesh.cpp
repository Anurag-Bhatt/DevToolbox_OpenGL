#include <glad/glad.h>
#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> &vertices)
: m_vertexCount(vertices.size() / 3), m_EBO(0)
{
     // Triangles have 3 vertices

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) , vertices.data() , GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices)
: m_indexCount(indices.size()), m_EBO(0)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
    if(m_EBO){
        glDeleteBuffers(1, &m_EBO);
    }
}

void Mesh::bind() const
{
    glBindVertexArray(m_VAO);
}

void Mesh::draw() const
{
    glBindVertexArray(m_VAO);
    if(m_EBO == 0){
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertexCount));
        
    }else{
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, 0);
    }
}
