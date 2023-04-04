﻿#pragma once
#include <cstdint>
#include <memory>

namespace Shard::Graphics
{
    class IndexBuffer
    {
    public:
        static std::shared_ptr<IndexBuffer> Create(const uint32_t* indices, uint32_t count);

        IndexBuffer(const uint32_t* indices, uint32_t count);
        ~IndexBuffer();
        
        void Bind() const;
        void Unbind() const;

        uint32_t GetCount() const { return m_count; }
    
    private:
        uint32_t m_bufferId;
        uint32_t m_count;
    };
}
