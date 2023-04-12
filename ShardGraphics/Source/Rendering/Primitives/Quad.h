#pragma once
#include <memory>
#include "Math/Math.h"

namespace Shard::Graphics
{
    class RenderCommand;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    /////////////////////////
    /// QUAD PRIMITIVE
    ////////////////////////
    
    class Quad
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 UV;
            glm::vec2 UVScale;
        };
        
        Quad();
        ~Quad();

        const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }

        void AddVertexData(const glm::mat4& modelMatrix, const glm::vec4& color, const glm::vec2& uvScale);
        const void* GetVertexData() const { return m_VertexData; }
        uint32_t GetIndexCount() const { return m_IndexCount; }
        
        uint32_t GetVertexDataSize() const
        {
            return static_cast<uint32_t>(reinterpret_cast<uint8_t*>(m_CurrentVertex) - reinterpret_cast<uint8_t*>(
                m_VertexData));
        }
        
        void ResetVertexData();
        
    private:
        const uint32_t m_MaxQuads;
        const uint32_t m_VertexCount;
        uint32_t m_IndexCount;
        const uint32_t m_VertexElementsCount;
        const uint32_t m_VertexDataCount;
        const uint32_t m_VertexDataSize;
        
        Vertex* m_VertexData;
        Vertex* m_CurrentVertex;
        uint32_t m_QuadCount;
        
        glm::vec3 m_VertexPositions[4];
        glm::vec2 m_VertexUV[4];
        
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}