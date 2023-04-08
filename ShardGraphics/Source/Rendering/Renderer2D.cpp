#include "Renderer2D.h"
#include "Camera/Camera.h"
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
        m_TrianglePrimitive = std::make_unique<TrianglePrimitive>();
        m_CommandQueue = std::make_unique<RenderCommandQueue>();
    }

    void Renderer2D::DrawPrimitives()
    {
        // TODO: Move this to other thread
        while(!m_CommandQueue->IsEmpty()) m_CommandQueue->ExecuteNext();
    }

    void Renderer2D::Finalize()
    {
    }

    void Renderer2D::Begin(const Camera& renderCamera)
    {
        m_SceneData.ProjectionViewMatrix = renderCamera.ProjectionViewMatrix();
    }

    void Renderer2D::Begin()
    {}

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

    void Renderer2D::SubmitPrimitive(const PrimitiveType type, const Transform& transform, const glm::vec4& color)
    {
        const glm::mat4 mvpMatrix = m_SceneData.ProjectionViewMatrix * glm::mat4(transform);
        
        switch (type)
        {
        case PrimitiveType::Triangle:
                m_CommandQueue->Submit<SetUniformMat4Command>(m_TrianglePrimitive->GetShader(), "u_MvpMatrix", mvpMatrix);
                m_CommandQueue->Submit<DrawElementsCommand>(m_TrianglePrimitive->GetVertexArray());
            return;
        }
    }
}
