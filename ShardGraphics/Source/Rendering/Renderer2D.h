#pragma once
#include <memory>
#include "Maths.h"
#include "Utility/Singleton.h"

#include "Structures/IndexBuffer.h"
#include "Structures/Shader.h"
#include "Structures/VertexBuffer.h"
#include "Structures/VertexArray.h"

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
        
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        
        std::unique_ptr<Shader> m_Shader;
    };
}
