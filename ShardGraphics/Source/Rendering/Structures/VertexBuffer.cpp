#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Shard::Graphics
{
    VertexBuffer* VertexBuffer::Create(const float* vertices, const uint32_t size)
    {
        return new VertexBuffer(vertices, size);
    }

    VertexBuffer::VertexBuffer(const float* vertices, const uint32_t size)
        : m_BufferId(0)
    {
        glCreateBuffers(1, &m_BufferId);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetLayout(const BufferLayout& bufferLayout)
    {
        m_Layout = bufferLayout;
    }
}