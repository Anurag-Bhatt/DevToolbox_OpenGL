#include <iostream>
#include <Object.hpp>

Object::Object(std::vector<float> meshVertices)
{
    m_mesh = std::make_shared<Mesh>(meshVertices);
}

Object::Object(std::vector<float> meshVertices, std::vector<unsigned int> meshVertexIndex)
{
    m_mesh = std::make_shared<Mesh>(meshVertices, meshVertexIndex);
}

Object::Object(std::shared_ptr<Mesh> mesh)
:m_mesh(mesh)
{
}

void Object::setTransform(glm::vec3 position)
{
    transform.Position = position;
}

glm::vec3 Object::getPosition()
{
    return transform.Position;
}

void Object::draw() const
{   
    // std::cout << "Drawing Mesh\n";
    if(m_mesh == nullptr){
        std::cout << "Error: Mesh not setup\n";
    }else{
        m_mesh->draw();
    }
}

void Object::setLayout(const std::vector<unsigned int> layout)
{
    std::cout << "Setting Layout \n";
    m_mesh->setLayout(layout);
}