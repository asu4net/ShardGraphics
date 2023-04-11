#include "Quad.h"
#include "Rendering/Data/IndexBuffer.h"
#include "Rendering/Data/VertexArray.h"
#include "Rendering/Data/VertexBuffer.h"

namespace Shard::Graphics
{
    Quad::Quad()
        : m_VertexCount(4)
        , m_VertexElementsCount(6)
        , m_VertexDataCount(m_VertexCount * m_VertexElementsCount)
        , m_VertexDataSize(m_VertexDataCount * sizeof(float))
        , m_VertexData(new Vertex[m_VertexCount])
    {
        constexpr uint32_t indices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        
        m_VertexArray = VertexArray::Create();
        
        m_VertexData[0] = {glm::vec3(-0.5, -0.5, 0.0f), { 0.0f, 0.0f } };
        m_VertexData[1] = {glm::vec3( 0.5, -0.5, 0.0f), { 1.0f, 0.0f } };
        m_VertexData[2] = {glm::vec3( 0.5,  0.5, 0.0f), { 1.0f, 1.0f } };
        m_VertexData[3] = {glm::vec3(-0.5,  0.5, 0.0f), { 0.0f, 1.0f } };
        
        m_VertexBuffer = VertexBuffer::Create(reinterpret_cast<const float*>(m_VertexData), m_VertexDataSize);

        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "a_UV"}
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_IndexBuffer = IndexBuffer::Create(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_VertexArray->Unbind();
    }

    Quad::~Quad()
    {
        delete[] m_VertexData;
    }
}
