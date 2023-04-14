#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

namespace Shard::Graphics
{
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filePath)
    {
        return std::make_shared<Texture2D>(filePath);
    }

    Texture2D::Texture2D(const std::string& filePath)
        : m_FilePath(filePath)
        , m_Width(0)
        , m_Height(0)
        , m_TextureID(0)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
        m_Width = width;
        m_Height = height;
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, GL_RGB8, m_Width, m_Height);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void Texture2D::Bind(const uint32_t slot) const
    {
        glBindTextureUnit(slot, m_TextureID);
    }
}
