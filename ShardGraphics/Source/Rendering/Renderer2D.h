#pragma once
#include "Utility/Singleton.h"
#include "Primitives/TrianglePrimitive.h"
#include "RenderCommandQueue.h"
#include <memory>

namespace Shard::Graphics
{
    struct RenderCamera
    {
        CameraConfiguration Configuration = {};
        Transform ViewTransform = {};
        float AspectRatio = 1280.f / 720.f;
        bool bAutoSetMatrices = true;
        glm::mat4 ProjectionMatrix = glm::IdentityMatrix;
        glm::mat4 ViewMatrix = glm::IdentityMatrix;
    };
    
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        Renderer2D() = default;
        Renderer2D(Renderer2D&&) = delete;
        
        void Initialize();
        void Update();
        void Finalize();

        void SetRenderCamera(const RenderCamera& renderCamera);
        void SetClearColor(const glm::vec4 clearColor);
        void Clear();
        void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void DrawPrimitive(PrimitiveType type, const Transform& transform = {}, const glm::vec4& color = glm::WhiteColor);

    private:
        RenderCamera m_RenderCamera;
        std::unique_ptr<RenderCommandQueue> m_CommandQueue;
        std::unique_ptr<TrianglePrimitive> m_TrianglePrimitive;
    };
}