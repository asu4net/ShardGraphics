#pragma once
#include <memory>
#include "Texture.h"
#include <string>

namespace Shard::Graphics
{
    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> Create(const std::string& filePath);
        Texture2D(const std::string& filePath);
        ~Texture2D();
        
        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }
        uint32_t GetTextureID() const override { return m_TextureID; }
        
        void Bind(uint32_t slot = 0) const override;

    private:
        std::string m_FilePath;
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_TextureID;
    };
}