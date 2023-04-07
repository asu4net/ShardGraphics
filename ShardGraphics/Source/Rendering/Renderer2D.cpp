#include "Renderer2D.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "Data/VertexArray.h"
#include "Data/Shader.h"

namespace Shard::Graphics
{
    void Renderer2D::Initialize()
    {
        m_TrianglePrimitive = std::make_unique<TrianglePrimitive>();
        m_CommandQueue = std::make_unique<RenderCommandQueue>();
    }

    void Renderer2D::Update()
    {
        // TODO: Move this to other thread
        while(!m_CommandQueue->IsEmpty()) m_CommandQueue->ExecuteNext();
    }

    void Renderer2D::Finalize()
    {
    }

    void Renderer2D::SetRenderCamera(const RenderCamera& renderCamera)
    {
        m_RenderCamera = renderCamera;

        if (!m_RenderCamera.bAutoSetMatrices) return;
        const auto& config = m_RenderCamera.Configuration;
        m_RenderCamera.ProjectionMatrix = config.CalculateProjectionMatrix(renderCamera.AspectRatio);
        m_RenderCamera.ViewMatrix = config.CalculateViewMatrix(renderCamera.ViewTransform);
    }

    void Renderer2D::SetClearColor(const glm::vec4 clearColor)
    {
        m_CommandQueue->Submit(std::make_shared<SetClearColorCommand>(clearColor));
    }

    void Renderer2D::Clear()
    {
        m_CommandQueue->Submit(std::make_shared<ClearCommand>());
    }

    void Renderer2D::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        m_CommandQueue->Submit(std::make_shared<SetViewPortCommand>(x, y, width, height));
    }

    void Renderer2D::DrawPrimitive(const PrimitiveType type, const Transform& transform, const glm::vec4& color)
    {
        const glm::mat4 mvpMatrix = m_RenderCamera.ProjectionMatrix * m_RenderCamera.ViewMatrix * glm::mat4(transform);
        
        switch (type)
        {
            case PrimitiveType::Triangle:
                //m_TrianglePrimitive->SetVertexData(mvpMatrix, color);
                m_TrianglePrimitive->GetShader()->Bind();
                m_TrianglePrimitive->GetShader()->SetUniformMat4("u_MvpMatrix", mvpMatrix);
                m_CommandQueue->Submit(m_TrianglePrimitive->CreateRenderCommand());
            return;
        }
    }
}
