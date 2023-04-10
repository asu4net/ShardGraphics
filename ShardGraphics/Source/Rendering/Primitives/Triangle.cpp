#include "Triangle.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Data/IndexBuffer.h"
#include "Rendering/Data/ShaderDataType.h"
#include "Rendering/Data/VertexArray.h"
#include "Rendering/Data/VertexBuffer.h"
#include <string>

namespace Shard::Graphics
{
    /////////////////////////
    /// TEST TRIANGLE
    ////////////////////////

    const uint32_t Triangle::VertexDataCount = 3 * 7;
    
    Triangle::Triangle()
        : m_VertexData(new Vertex[VertexDataCount])
    {
        constexpr uint32_t indices[3] = { 0, 1, 2 };
        
        m_VertexArray = VertexArray::Create();

        m_VertexData[0] = {glm::vec3(-0.5f, -0.5f, 0.0f), {0.8f, 0.2f, 0.8f, 1.0f} };
        m_VertexData[1] = {glm::vec3( 0.5f, -0.5f, 0.0f), {0.2f, 0.3f, 0.8f, 1.0f} };
        m_VertexData[2] = {glm::vec3( 0.0f,  0.5f, 0.0f), {0.8f, 0.8f, 0.2f, 1.0f} };
        
        m_VertexBuffer = VertexBuffer::Create(reinterpret_cast<const float*>(m_VertexData), VertexDataCount * sizeof(float));

        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_IndexBuffer = IndexBuffer::Create(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        m_VertexArray->Unbind();
    }

    Triangle::~Triangle()
    {
        delete[] m_VertexData;
    }
}