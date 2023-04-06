#pragma once
#include <cstdint>
#include <memory>

namespace Shard::Graphics
{
    class IndexBuffer
    {
    public:
        static IndexBuffer* Create(const uint32_t* indices, uint32_t count);

        IndexBuffer(const uint32_t* indices, uint32_t count);
        ~IndexBuffer();
        
        void Bind() const;
        void Unbind() const;

        uint32_t GetCount() const { return m_Count; }
    
    private:
        uint32_t m_BufferId;
        uint32_t m_Count;
    };
}
