#include "Renderer2D.h"
#include <glad/glad.h>

namespace Shard::Graphics
{
    /////////////////////////
    /// TEST TRIANGLE
    ////////////////////////

    static GLenum ShaderDataTypeToOpenGlBaseType(const ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::None:   return 0;
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_BOOL;
        default:                     return 0;
        }
    }
    
    void Renderer2D::Initialize()
    {
        /////////////////////////
        /// TEST TRIANGLE
        ////////////////////////

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, static_cast<uint32_t>(sizeof(vertices)));

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        const BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        m_vertexBuffer->SetLayout(layout);
        
        uint32_t index = 0;
        for (const auto& element : m_vertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGlBaseType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const void*>(element.offset)
                );
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_indexBuffer = std::make_unique<IndexBuffer>(indices, static_cast<uint32_t>(sizeof(indices) / sizeof(uint32_t)));
        
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
         
         m_shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }
    
    void Renderer2D::ClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /////////////////////////
        /// TEST TRIANGLE
        ////////////////////////
        
        m_shader->Bind();
        glBindVertexArray(m_vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }
}