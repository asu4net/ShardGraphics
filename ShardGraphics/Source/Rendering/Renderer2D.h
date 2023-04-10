#pragma once
#include "Utility/Singleton.h"
#include "Primitives/Triangle.h"
#include "Primitives/Quad.h"
#include "RenderCommandQueue.h"
#include <memory>

namespace Shard::Graphics
{
    class ViewportCamera;
    class Window;

    enum class PrimitiveType
    {
        Triangle, Quad
    };
    
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        std::shared_ptr<Shader> FlatColorShader() const
        {
            return m_FlatColorShader;
        }

        std::shared_ptr<Shader> VertexColorShader() const
        {
            return m_VertexColorShader;
        }

        std::shared_ptr<Shader> TextedQuadShader() const
        {
            return m_TextedQuadShader;
        }

        Renderer2D() = default;
        Renderer2D(Renderer2D&&) = delete;

        static Renderer2D& CreateAndInitialize(const std::shared_ptr<Window>& window);
        static void FinalizeAndDestroy();
        
        void Initialize();
        void DrawPrimitives();
        void Finalize();

        void SetProjectionViewMatrix(const glm::mat4& projectionViewMatrix);
        
        void ClearScreen(const glm::vec4 clearColor = Global::DarkGreyColor);
        void SetClearColor(const glm::vec4 clearColor);
        void Clear();
        void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void SubmitPrimitive(
            PrimitiveType type,
            const glm::mat4& modelMatrix = Global::IdentityMatrix,
            const glm::vec4& color = Global::WhiteColor,
            const std::shared_ptr<Shader>& shader = nullptr);

        

    private:
        struct SceneData
        {
            glm::mat4 ProjectionViewMatrix = Global::IdentityMatrix;
        };
        
        SceneData m_SceneData;
        std::unique_ptr<RenderCommandQueue> m_CommandQueue;
        std::unique_ptr<Triangle> m_TrianglePrimitive;
        std::unique_ptr<Quad> m_QuadPrimitive;
        
        std::shared_ptr<Shader> m_FlatColorShader;
        std::shared_ptr<Shader> m_VertexColorShader;
        std::shared_ptr<Shader> m_TextedQuadShader;
    };
}
