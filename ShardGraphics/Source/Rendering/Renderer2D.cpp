#include "Renderer2D.h"

#include <array>

#include "Window/Window.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "Data/VertexArray.h"
#include "Data/Shader.h"
#include "Data/VertexBuffer.h"

namespace Shard::Graphics
{
    struct QuadData
    {
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 UV;
            glm::vec2 UVScale;
            float TextureSlot;
        };

        static constexpr uint32_t MaxQuads = 10000;
        static constexpr uint32_t MaxTextureSlots = 32;
        
        static constexpr uint32_t MaxVertices = MaxQuads * 4;
        
        static constexpr glm::vec3 QuadVertexPositions[] = {
            {-0.5, -0.5, 0.0f},
            {0.5, -0.5, 0.0f},
            {0.5, 0.5, 0.0f},
            {-0.5, 0.5, 0.0f}
        };

        static constexpr glm::vec2 QuadVertexUV[] = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<VertexBuffer> VertexBuffer;
        std::shared_ptr<IndexBuffer> IndexBuffer;

        Vertex* VertexData = nullptr;
        Vertex* LastVertex = nullptr;
        uint32_t QuadCount = 0;
        
        std::array<std::shared_ptr<Texture>, MaxTextureSlots> Indices;
        uint32_t LastIndex = 1;
        uint32_t IndexCount = 0;

        uint32_t Samplers[MaxTextureSlots];
    };

    static QuadData g_QuadData;
    
    Renderer2D& Renderer2D::CreateAndInitialize(const std::shared_ptr<Window>& window)
    {
        Renderer2D& renderer2D = Renderer2D::CreateSingleton();
        renderer2D.Initialize();
        renderer2D.SetViewPort(0, 0, window->GetWidth(), window->GetHeight());
        return renderer2D;
    }

    void Renderer2D::FinalizeAndDestroy()
    {
        Renderer2D& renderer2D = GetInstance();
        renderer2D.Finalize();
        DestroySingleton();
    }

    void Renderer2D::Initialize()
    {
        m_CommandQueue = std::make_unique<RenderCommandQueue>();
        m_TrianglePrimitive = std::make_unique<Triangle>();
        
        m_FlatColorShader = Shader::Create("Content/Shaders/FlatColor.glsl");
        m_VertexColorShader = Shader::Create("Content/Shaders/VertexColor.glsl");
        m_TextureShader = Shader::Create("Content/Shaders/Texture.glsl");
        
        g_QuadData.VertexArray = VertexArray::Create();
        g_QuadData.VertexBuffer = VertexBuffer::Create(QuadData::MaxVertices * sizeof(QuadData::Vertex));
        
        g_QuadData.VertexData = new QuadData::Vertex[QuadData::MaxVertices];
    }

    void Renderer2D::DrawPrimitives()
    {
        // TODO: Move this to other thread
        while(!m_CommandQueue->IsEmpty()) m_CommandQueue->ExecuteNext();
    }

    void Renderer2D::Finalize()
    {
    }

    

    void Renderer2D::SetProjectionViewMatrix(const glm::mat4& projectionViewMatrix)
    {
        m_SceneData.ProjectionViewMatrix = projectionViewMatrix;
    }

    void Renderer2D::ClearScreen(const glm::vec4 clearColor)
    {
        SetClearColor(clearColor);
        Clear();
    }

    void Renderer2D::SetClearColor(const glm::vec4 clearColor)
    {
        m_CommandQueue->Submit<SetClearColorCommand>(clearColor);
    }

    void Renderer2D::Clear()
    {
        m_CommandQueue->Submit<ClearCommand>();
    }

    void Renderer2D::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        m_CommandQueue->Submit<SetViewPortCommand>(x, y, width, height);
    }

    void Renderer2D::SubmitPrimitive(
        const PrimitiveType type,
        const glm::mat4& modelMatrix,
        const glm::vec4& color,
        const std::shared_ptr<Shader>& shader,
        const std::shared_ptr<Texture>& texture)
    {
        const glm::mat4 mvpMatrix = m_SceneData.ProjectionViewMatrix * modelMatrix;
        const std::shared_ptr<Shader> shaderToUse = shader ? shader : m_FlatColorShader;
        
        switch (type)
        {
        case PrimitiveType::Triangle:
            m_CommandQueue->Submit<SetUniformMat4Command>(m_VertexColorShader, "u_MvpMatrix", mvpMatrix);
            m_CommandQueue->Submit<DrawElementsCommand>(m_TrianglePrimitive->GetVertexArray());
            return;

        case PrimitiveType::Quad:
            m_CommandQueue->Submit<SetUniformMat4Command>(shaderToUse, "u_MvpMatrix", mvpMatrix);
            m_CommandQueue->Submit<SetUniformVec4Command>(shaderToUse, "u_Color", color);
            m_CommandQueue->Submit<DrawElementsCommand>(m_QuadPrimitive->GetVertexArray());
            return;
            
        case PrimitiveType::TextedQuad:
            m_CommandQueue->Submit<SetUniformMat4Command>(shaderToUse, "u_MvpMatrix", mvpMatrix);
            m_CommandQueue->Submit<SetUniformVec4Command>(shaderToUse, "u_Color", color);
            m_CommandQueue->Submit<BindTextureCommand>(texture);
            m_CommandQueue->Submit<SetUniformIntCommand>(shaderToUse, "u_TextureSlot", 0);
            m_CommandQueue->Submit<DrawElementsCommand>(m_QuadPrimitive->GetVertexArray());
            return;
        }
    }
}
