﻿#pragma once
#include <array>
#include <memory>
#include "Maths.h"

namespace Shard::Graphics
{
    class RenderCommand;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;

    enum class PrimitiveType
    {
        Triangle
    };

    /////////////////////////
    /// TEST TRIANGLE
    ////////////////////////
    
    class TrianglePrimitive
    {
    public:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
        };

        static const uint32_t VertexDataCount;
        
        TrianglePrimitive();
        ~TrianglePrimitive();

        void SetVertexData(const Transform& transform, const glm::vec4& color);
        
        const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }
        std::shared_ptr<RenderCommand> CreateRenderCommand();
        
    private:
        Vertex* m_VertexData;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Shader> m_Shader;
    };
}