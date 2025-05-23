#pragma once

#include <vector>

class Mesh{

public:
    Mesh();
    ~Mesh();

    void bind()const;
    void draw()const;

private:

    unsigned int VAO, VBO;
    int vertexCount;
};
