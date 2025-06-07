#pragma once

#include <vector>
#include <memory>

#include <Mesh.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>


struct Transform{
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;
};


class Object{

public: 


    Object(std::vector<float> meshVertices);
    Object(std::vector<float> meshVertices, std::vector<unsigned int> meshVertexIndex);

    Object(std::shared_ptr<Mesh> mesh);

    ~Object() = default;

    void setTransform(glm::vec3 position);

    glm::vec3 getPosition();

    void draw() const;
    void setLayout(const std::vector<unsigned int> layout);

private:

    std::shared_ptr<Mesh> m_mesh;
    Transform transform;

};