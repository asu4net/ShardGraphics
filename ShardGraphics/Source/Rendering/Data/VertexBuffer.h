#pragma once
#include <cstdint>
#include <memory>

#include "BufferLayout.h"

namespace Shard::Graphics
{
    class VertexBuffer
    {
    public:
        static VertexBuffer* Create(const float* vertices, uint32_t size);
        static VertexBuffer* Create(uint32_t size);
        
        VertexBuffer(const float* vertices, uint32_t size);
        VertexBuffer(uint32_t size);
        ~VertexBuffer();
        
        void Bind() const;
        void Unbind() const;
        void SetData(const void* data, uint32_t size);
        
        void SetLayout(const BufferLayout& bufferLayout);
        const BufferLayout& GetLayout() const { return m_Layout; }
    
    private:
        uint32_t m_BufferId{};
        BufferLayout m_Layout;
    };
}
