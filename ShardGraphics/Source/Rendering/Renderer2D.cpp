#include "Renderer2D.h"
#include <glad/glad.h>

namespace Shard::Graphics
{
    void Renderer2D::Initialize()
    {
        /////////////////////////
        /// TEST TRIANGLE
        ////////////////////////

        m_VertexArray = VertexArray::Create();

        constexpr float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        
        m_VertexBuffer = VertexBuffer::Create(vertices, static_cast<uint32_t>(sizeof(vertices)));

        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        const BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        m_VertexBuffer->SetLayout(layout);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        constexpr  uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer = IndexBuffer::Create(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->AddIndexBuffer(m_IndexBuffer);
        
         std::string vertexSource = R"(
             #version 410 core
             
             layout(location = 0) in vec3 a_Position;
             layout(location = 1) in vec4 a_Color;

             out vec4 v_Color;

             void main()
             {
                 gl_Position = vec4(a_Position, 1.0);
                 v_Color = a_Color;
             }
         )";
         
         std::string fragmentSource = R"(
             #version 410 core
             
             layout(location = 0) out vec4 color;
             in vec4 v_Color;
             
             void main()
             {
                 color = v_Color;
             }
         )";
         
         m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }
    
    void Renderer2D::ClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /////////////////////////
        /// TEST TRIANGLE
        ////////////////////////
        
        m_Shader->Bind();
        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }
}