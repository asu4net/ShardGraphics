#pragma once
#include <string>

#include "glm/fwd.hpp"

namespace Shard::Graphics
{
    class Shader
    {
    public:
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();
        
        void SetUniformMat4(const char* uniformName, const glm::mat4& mat) const;
        void SetUniformVec4(const char* uniformName, const glm::vec4& vec) const;
        
        void Bind() const;
        void Unbind() const;
        
    private:
        uint32_t m_ShaderId;
    };
}
