#pragma once

#include <vector>

class Mesh{

public:
    Mesh(std::vector<float> &vertices);
    Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);
    ~Mesh();

    void bind()const;
    void draw()const;

private:

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
    int m_vertexCount = 0, m_indexCount = 0;
};
