#include "Renderer2D.h"
#include "Window/Window.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "Data/VertexArray.h"
#include "Data/Shader.h"

namespace Shard::Graphics
{
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
        m_QuadPrimitive = std::make_unique<Quad>();
        
        m_FlatColorShader = Shader::Create("Content/Shaders/FlatColor.glsl");
        m_VertexColorShader = Shader::Create("Content/Shaders/VertexColor.glsl");
        m_TextedQuadShader = Shader::Create("Content/Shaders/TextedQuad.glsl");
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

    void Renderer2D::SubmitPrimitive(const PrimitiveType type, const glm::mat4& modelMatrix, const glm::vec4& color
        , const std::shared_ptr<Shader>& shader)
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
        }
    }
}