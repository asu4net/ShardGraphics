#include "Renderer2D.h"

#include <array>

#include "Window/Window.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"
#include "Data/IndexBuffer.h"
#include "Data/VertexArray.h"
#include "Data/Shader.h"
#include "Data/Texture2D.h"
#include "Data/VertexBuffer.h"

namespace Shard::Graphics
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 UV;
        glm::vec2 UVScale;
        uint32_t TextureSlot;
    };
    
    struct QuadData
    {
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

        QuadVertex* VertexData = nullptr;
        QuadVertex* LastVertex = nullptr;
        uint32_t QuadCount = 0;
        
        std::array<std::shared_ptr<Texture>, MaxTextureSlots> Textures;
        std::shared_ptr<Texture> WhiteTexture;
        uint32_t LastTextureSlot = 1;
        uint32_t IndexCount = 0;
    };

    static QuadData g_QuadData;
    static int32_t g_TextureSlots[QuadData::MaxTextureSlots];
    
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

        g_QuadData.VertexData = new QuadVertex[QuadData::MaxVertices];
        g_QuadData.LastVertex = g_QuadData.VertexData;
        g_QuadData.WhiteTexture = Texture2D::Create("Content/Textures/blank.png");
        g_QuadData.Textures[0] = g_QuadData.WhiteTexture;
        
        g_QuadData.VertexArray = VertexArray::Create();
        g_QuadData.VertexBuffer = VertexBuffer::Create(QuadData::MaxVertices * sizeof(QuadVertex));
        g_QuadData.VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_UV"},
            {ShaderDataType::Float2, "a_UVScale"},
            {ShaderDataType::Float, "a_TextureSlot"}
        });
        g_QuadData.VertexArray->AddVertexBuffer(g_QuadData.VertexBuffer);

        constexpr uint32_t maxIndices = QuadData::MaxQuads * 6;
        
        uint32_t* indices = new uint32_t[maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }
        
        g_QuadData.IndexBuffer = IndexBuffer::Create(indices, maxIndices);
        g_QuadData.VertexArray->SetIndexBuffer(g_QuadData.IndexBuffer);
        
        delete[] indices;

        for (uint32_t i = 0; i < QuadData::MaxTextureSlots; i++)
            g_TextureSlots[i] = i;
    }

    void Renderer2D::Finalize() {}

    int GetTextureSlot(const std::shared_ptr<Texture>& texture)
    {
        int textureSlot = 0.f;

        if (texture)
        {
            // Search existing texture
            for (uint32_t i = 1; i < g_QuadData.LastTextureSlot; i++)
            {
                if (g_QuadData.Textures[i]->GetTextureID() == texture->GetTextureID())
                {
                    textureSlot = i;
                    break;
                }
            }

            // If not exists save the new texture
            if (textureSlot == 0)
            {
                g_QuadData.Textures[g_QuadData.LastTextureSlot] = texture;
                textureSlot = g_QuadData.LastTextureSlot;
                g_QuadData.LastTextureSlot++;
            }
        }

        return textureSlot;
    }

    void Renderer2D::SubmitQuad(const glm::mat4& modelMatrix, const glm::vec4& color,
        const std::shared_ptr<Texture>& texture, const glm::vec2& uvScale)
    {
        if (g_QuadData.QuadCount > QuadData::MaxQuads || g_QuadData.LastTextureSlot > QuadData::MaxTextureSlots)
            NextBatch();
        
        for (int i = 0; i < 4; i++)
        {
            g_QuadData.LastVertex->Position =  modelMatrix * glm::vec4(QuadData::QuadVertexPositions[i], 1.0f);
            g_QuadData.LastVertex->Color = color;
            g_QuadData.LastVertex->UV = QuadData::QuadVertexUV[i];
            g_QuadData.LastVertex->UVScale = uvScale;
            g_QuadData.LastVertex->TextureSlot = GetTextureSlot(texture);
            g_QuadData.LastVertex++;
        }

        g_QuadData.IndexCount += 6;
        g_QuadData.QuadCount++;
    }

    void Renderer2D::SubmitPrimitive(
        const PrimitiveType type,
        const glm::mat4& modelMatrix,
        const glm::vec4& color,
        const std::shared_ptr<Texture>& texture)
    {
        const glm::mat4 mvpMatrix = m_SceneData.ProjectionViewMatrix * modelMatrix;
        
        switch (type)
        {
        case PrimitiveType::Triangle:
            m_CommandQueue->Submit<SetUniformMat4Command>(m_VertexColorShader, "u_MvpMatrix", mvpMatrix);
            m_CommandQueue->Submit<DrawElementsCommand>(m_TrianglePrimitive->GetVertexArray(),
                m_TrianglePrimitive->GetVertexArray()->GetIndexBuffer()->GetCount());
            return;

        case PrimitiveType::Quad:
            SubmitQuad(modelMatrix, color, texture, Global::OneVector);
            return;
        }
    }

    void Renderer2D::Flush()
    {
        g_QuadData.VertexBuffer->SetData(g_QuadData.VertexData, static_cast<uint32_t>(reinterpret_cast<uint8_t*>(g_QuadData.LastVertex) -
                        reinterpret_cast<uint8_t*>(g_QuadData.VertexData)));
        
        for (uint32_t i = 0; i < g_QuadData.LastTextureSlot; i++)
                    g_QuadData.Textures[i]->Bind(i);
        
        m_CommandQueue->Submit<SetUniformMat4Command>(m_TextureShader, "u_ProjectionViewMatrix", m_SceneData.ProjectionViewMatrix);
        m_CommandQueue->Submit<DrawElementsCommand>(g_QuadData.VertexArray, g_QuadData.IndexCount);
        
        // TODO: Move this to other thread
        while(!m_CommandQueue->IsEmpty()) m_CommandQueue->ExecuteNext();
    }

    void Renderer2D::NextBatch()
    {
        Flush();
        StartBatch();
    }

    void Renderer2D::Begin(const glm::mat4& projectionViewMatrix)
    {
        m_SceneData.ProjectionViewMatrix = projectionViewMatrix;
        m_TextureShader->Bind();
        m_TextureShader->SetUniformMat4("u_ProjectionViewMatrix", m_SceneData.ProjectionViewMatrix);
        m_TextureShader->SetUniformIntArray("u_TextureSlots", g_TextureSlots, QuadData::MaxQuads);

        StartBatch();
    }

    void Renderer2D::StartBatch()
    {
        g_QuadData.LastVertex = g_QuadData.VertexData;
        g_QuadData.QuadCount = 0;
        g_QuadData.IndexCount = 0;
        g_QuadData.LastTextureSlot = 1;
    }

    void Renderer2D::End()
    {
        Flush();
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
}