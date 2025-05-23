#include <glad/glad.h>
#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> &vertices)
{
    m_vertexCount = vertices.size() / 3; // Triangles have 3 vertices

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) , vertices.data() , GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::bind() const
{
    glBindVertexArray(m_VAO);
}

void Mesh::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}
