#pragma once
#include <string>

namespace Shard::Graphics
{
    class Shader
    {
    public:
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();
        
        void Bind() const;
        void Unbind() const;
        
    private:
        uint32_t m_ShaderId;
    };
}