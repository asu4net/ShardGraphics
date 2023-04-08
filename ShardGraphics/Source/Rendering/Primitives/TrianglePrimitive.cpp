#include "TrianglePrimitive.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Data/IndexBuffer.h"
#include "Rendering/Data/Shader.h"
#include "Rendering/Data/ShaderDataType.h"
#include "Rendering/Data/VertexArray.h"
#include "Rendering/Data/VertexBuffer.h"
#include <string>

namespace Shard::Graphics
{
    /////////////////////////
    /// TEST TRIANGLE
    ////////////////////////

    const uint32_t TrianglePrimitive::VertexDataCount = 3 * 7;
    
    TrianglePrimitive::TrianglePrimitive()
        : m_VertexData(new Vertex[VertexDataCount])
    {
        constexpr uint32_t indices[3] = { 0, 1, 2 };

        m_VertexData[0] = { glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::WhiteColor };
        m_VertexData[1] = { glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f), glm::WhiteColor };
        m_VertexData[2] = { glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f), glm::WhiteColor };
        
        m_VertexArray.reset(VertexArray::Create());
        m_VertexBuffer.reset(VertexBuffer::Create(reinterpret_cast<const float*>(m_VertexData), VertexDataCount * sizeof(float)));
        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
        });
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_IndexBuffer.reset(IndexBuffer::Create(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t))));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        
        const std::string vertexSource = R"(
             #version 410 core
             
             layout(location = 0) in vec3 a_Position;
             layout(location = 1) in vec4 a_Color;
             uniform mat4 u_MvpMatrix;
             uniform vec4 u_Color;

             out vec4 v_Color;

             void main()
             {
                 gl_Position = u_MvpMatrix * vec4(a_Position, 1.0);
                 v_Color = u_Color;
             }
         )";

        const std::string fragmentSource = R"(
             #version 410 core
             
             layout(location = 0) out vec4 color;
             in vec4 v_Color;
             
             void main()
             {
                 color = v_Color;
             }
         )";
        
        m_Shader.reset(Shader::Create(vertexSource, fragmentSource));
    }

    TrianglePrimitive::~TrianglePrimitive()
    {
        delete[] m_VertexData;
    }

    void TrianglePrimitive::SetVertexData(const glm::mat4 mvpMatrix, const glm::vec4& color)
    {
        m_VertexData[0] = { mvpMatrix * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), color };
        m_VertexData[1] = { mvpMatrix * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f), color };
        m_VertexData[2] = { mvpMatrix * glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f), color };
        m_VertexBuffer->SetData(m_VertexData, static_cast<uint32_t>(VertexDataCount * sizeof(float)));
    }
}