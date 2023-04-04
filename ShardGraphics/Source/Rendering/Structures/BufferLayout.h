#pragma once
#include <vector>
#include "BufferElement.h"

namespace Shard::Graphics
{
    class BufferLayout
    {
    public:
        BufferLayout()
            : m_stride(0)
        {}
        
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_stride(0)
            , m_elements(elements)
        {
            uint32_t offset = 0;
            m_stride = 0;
            for (auto& element : m_elements)
            {
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }
        
        const std::vector<BufferElement>& GetElements() const { return m_elements; }
        uint32_t GetStride() const { return m_stride; }
        
        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
        
    private:
        uint32_t m_stride;
        std::vector<BufferElement> m_elements;
    };
}
