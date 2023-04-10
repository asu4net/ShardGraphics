﻿#pragma once
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
        static std::shared_ptr<VertexArray> Create();
        
        VertexArray();
        ~VertexArray();
        
        void Bind() const;
        void Unbind() const;
        
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
        
    private:
        uint32_t m_VertexArrayId;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}
