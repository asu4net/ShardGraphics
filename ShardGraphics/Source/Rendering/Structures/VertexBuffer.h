#pragma once
#include <cstdint>
#include <memory>

#include "BufferLayout.h"

namespace Shard::Graphics
{
    class VertexBuffer
    {
    public:
        static std::shared_ptr<VertexBuffer> Create(const float* vertices, uint32_t size);
        
        VertexBuffer(const float* vertices, uint32_t size);
        ~VertexBuffer();
        
        void Bind() const;
        void Unbind() const;
        
        void SetLayout(const BufferLayout& bufferLayout);
        const BufferLayout& GetLayout() const { return m_layout; }
    
    private:
        uint32_t m_bufferId;
        BufferLayout m_layout;
    };
}
