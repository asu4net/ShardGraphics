#pragma once
#include "Utility/Singleton.h"
#include "RenderCommandQueue.h"
#include "Math/Math.h"
#include <memory>

namespace Shard::Graphics
{
    class ViewportCamera;
    class Window;

    struct Quad
    {
        glm::mat4 ModelMatrix = Global::IdentityMatrix;
        glm::vec4 Color = Global::WhiteColor;
        std::shared_ptr<Texture> Texture = nullptr;
        bool bIsSubTexture = false;
        glm::vec2 SubTextureSize = Global::OneVector;
        glm::vec2 LocationInAtlas = Global::ZeroVector;
        glm::vec2 UVScale = Global::OneVector;
        glm::vec2 Size = Global::OneVector;
    };

    struct Renderer2DSettings
    {
        bool bReadShadersFromFiles = true;
        std::string FlatColorShaderLocation = "Content/Shaders/FlatColor.glsl";
        std::string TextureShaderLocation = "Content/Shaders/Texture.glsl";
    };
    
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        std::shared_ptr<Shader> FlatColorShader() const { return m_FlatColorShader; }
        std::shared_ptr<Shader> TextureShader() const { return m_TextureShader; }

        Renderer2D() = default;
        Renderer2D(Renderer2D&&) = delete;

        static Renderer2D& CreateAndInitialize(const std::shared_ptr<Window>& window);
        static void FinalizeAndDestroy();
        
        void Initialize(const Renderer2DSettings& rendererSettings = {});
        void Finalize();

        void Begin(const glm::mat4& projectionViewMatrix = Global::IdentityMatrix);
        void End();
        
        const std::unique_ptr<RenderCommandQueue>& CommandQueue() const { return m_CommandQueue; } 
        
        void ClearScreen(const glm::vec4 clearColor = Global::DarkGreyColor);
        void SetClearColor(const glm::vec4 clearColor);
        void Clear();
        void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void SubmitQuad(const Quad& quadProperties);

    private:
        struct SceneData
        {
            glm::mat4 ProjectionViewMatrix = Global::IdentityMatrix;
        };
        SceneData m_SceneData;
        std::unique_ptr<RenderCommandQueue> m_CommandQueue;
        
        std::shared_ptr<Shader> m_FlatColorShader;
        std::shared_ptr<Shader> m_TextureShader;

        void StartBatch();
        void Flush();
        void NextBatch();
        void CreateShaders(const Renderer2DSettings& rendererSettings);
    };
}
