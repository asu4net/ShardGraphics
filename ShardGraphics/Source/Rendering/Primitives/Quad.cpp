#include "Quad.h"
#include "Rendering/Data/IndexBuffer.h"
#include "Rendering/Data/VertexArray.h"
#include "Rendering/Data/VertexBuffer.h"

namespace Shard::Graphics
{
    Quad::Quad()
        : m_MaxQuads(10000)
        , m_VertexCount(m_MaxQuads * 4)
        , m_VertexElementsCount(6)
        , m_VertexDataCount(m_VertexCount * m_VertexElementsCount)
        , m_VertexDataSize(m_VertexDataCount * sizeof(float))
        , m_VertexData(new Vertex[m_VertexCount])
        , m_CurrentVertex(m_VertexData)
        , m_QuadCount(0)
        , m_IndexCount(0)
        , m_VertexPositions{
            {-0.5, -0.5, 0.0f},
            {0.5, -0.5, 0.0f},
            {0.5, 0.5, 0.0f},
            {-0.5, 0.5, 0.0f}
        }
        , m_VertexUV{
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        }
    {
        m_VertexArray = VertexArray::Create();
        m_VertexBuffer = VertexBuffer::Create(m_VertexDataSize);

        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_UV"},
            {ShaderDataType::Float2, "a_UVScale"},
             {ShaderDataType::Float, "a_TextureSlot"}
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        const uint32_t maxIndices = m_MaxQuads * 6;
        uint32_t* indices = new uint32_t[maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }
        
        m_IndexBuffer = IndexBuffer::Create(indices, maxIndices);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        delete[] indices;

        m_VertexArray->Unbind();
    }

    Quad::~Quad()
    {
        delete[] m_VertexData;
    }

    void Quad::AddVertexData(const glm::mat4& modelMatrix, const glm::vec4& color, const float textureSlot, const glm::vec2& uvScale)
    {
        for (int i = 0; i < 4; i++)
        {
            m_CurrentVertex->Position =  modelMatrix * glm::vec4(m_VertexPositions[i], 1.0f);
            m_CurrentVertex->Color = color;
            m_CurrentVertex->UV = m_VertexUV[i];
            m_CurrentVertex->UVScale = uvScale;
            m_CurrentVertex->TextureSlot = textureSlot;
            m_CurrentVertex++;
        }

        m_IndexCount += 6;
        m_QuadCount++;
    }

    void Quad::ResetVertexData()
    {
        m_CurrentVertex = m_VertexData;
        m_QuadCount = 0;
        m_IndexCount = 0;
    }
}