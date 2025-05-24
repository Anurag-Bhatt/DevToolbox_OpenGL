#pragma once

#include <string>

class Texture {

public:

    Texture(const std::string &texPath);
    ~Texture();

    void bind(unsigned int unit = 0) const;
    void unbind() const;

    unsigned int getID() const {return m_ID;};


private:

    unsigned int m_ID;
    int m_width, m_height, m_channels;
};