#include <glad/glad.h>
#include <iostream>
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &texPath)
{
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texPath.c_str(), &m_width, &m_height, &m_channels, 4);

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if (data)
    {
        std::cout << "Num of channels: " << m_channels << std::endl;
        GLenum format = GL_RGB;
        if(m_channels == 1)
            format = GL_RED;
        else if (m_channels == 3)
            format = GL_RGB8;
        else if (m_channels == 4)
            format = GL_RGBA8;

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture at: " << texPath << std::endl;
    }
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::bind(unsigned int unit) const{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}