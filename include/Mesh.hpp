#pragma once

#include <vector>

class Mesh{

public:
    Mesh(std::vector<float> &vertices);
    Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);
    ~Mesh();

    void bind()const;
    void unbind()const;
    void draw()const;

    void setLayout(const std::vector<unsigned int> &layout);

private:

    void setupAttribs();

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
    int m_vertexCount = 0, m_indexCount = 0;
    

    std::vector<unsigned int> m_layout;
    unsigned int m_stride;

};
