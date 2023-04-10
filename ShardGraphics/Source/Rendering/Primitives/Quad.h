#pragma once
#include <memory>
#include "Math/Math.h"

namespace Shard::Graphics
{
    class RenderCommand;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    /////////////////////////
    /// QUAD PRIMITIVE
    ////////////////////////
    
    class Quad
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec2 UV;
        };

        static const uint32_t VertexCount;
        static const uint32_t VertexDataCount;
        
        Quad();
        ~Quad();

        const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }
        
    private:
        Vertex* m_VertexData;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}