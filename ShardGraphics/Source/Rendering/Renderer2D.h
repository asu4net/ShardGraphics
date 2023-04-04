#pragma once
#include <memory>
#include "Maths.h"
#include "Utility/Singleton.h"

#include "Structures/IndexBuffer.h"
#include "Structures/Shader.h"
#include "Structures/VertexBuffer.h"

namespace Shard::Graphics
{
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        void Initialize();
        void ClearColor(const glm::vec4& color);

    private:
        /////////////////////////
        /// TEST TRIANGLE
        ////////////////////////
        
        uint32_t m_vertexArray = 0;
        
        std::unique_ptr<VertexBuffer> m_vertexBuffer;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
        std::unique_ptr<Shader> m_shader;
    };
}