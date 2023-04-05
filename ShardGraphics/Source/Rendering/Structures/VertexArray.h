#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace Shard::Graphics
{
    class VertexBuffer;
    class IndexBuffer;
    
    class VertexArray
    {
    public:
        static VertexArray* Create();
        
        VertexArray();
        ~VertexArray();
        
        void Bind() const;
        void Unbind() const;
        
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
        
    private:
        uint32_t m_VertexArrayId;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;
    };
}
