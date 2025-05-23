#pragma once

#include <vector>

class Mesh{

public:
    Mesh(std::vector<float> &vertices);
    ~Mesh();

    void bind()const;
    void draw()const;

private:

    unsigned int m_VAO, m_VBO;
    int m_vertexCount;
};
