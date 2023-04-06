#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Maths.h"

namespace Shard::Graphics
{
    class VertexArray;
    
    class RendererAPI
    {
    public:
        static RendererAPI* Create();
        
        RendererAPI() = default;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void SetClearColor(const glm::vec4& clearColor);
        void Clear();
        void DrawElements(const std::shared_ptr<VertexArray>& vertexArray);
    };
}
