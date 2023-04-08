﻿#pragma once
#include "Utility/Singleton.h"
#include "Primitives/TrianglePrimitive.h"
#include "RenderCommandQueue.h"
#include <memory>

namespace Shard::Graphics
{
    class Camera;
    class Window;
    
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        Renderer2D() = default;
        Renderer2D(Renderer2D&&) = delete;

        static Renderer2D& CreateAndInitialize(const std::shared_ptr<Window>& window);
        static void FinalizeAndDestroy();
        
        void Initialize();
        void Update();
        void Finalize();

        void Begin(const Camera& renderCamera);
        void ClearScreen(const glm::vec4 clearColor = glm::DarkGreyColor);
        void SetClearColor(const glm::vec4 clearColor);
        void Clear();
        void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void DrawPrimitive(PrimitiveType type, const Transform& transform = {}, const glm::vec4& color = glm::WhiteColor);

    private:
        struct SceneData
        {
            glm::mat4 ProjectionViewMatrix = glm::IdentityMatrix;
        };
        
        SceneData m_SceneData;
        std::unique_ptr<RenderCommandQueue> m_CommandQueue;
        std::unique_ptr<TrianglePrimitive> m_TrianglePrimitive;
    };
}
