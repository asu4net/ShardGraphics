﻿#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Math.h"

namespace Shard::Graphics
{
    class VertexArray;

    enum class BlendingMode
    {
        Alpha,
        Solid,
        Add,
        Multiply
    };
    
    class RendererAPI
    {
    public:
        static RendererAPI* Create();
        
        RendererAPI() = default;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        void SetClearColor(const glm::vec4& clearColor);
        void Clear();
        void SetBlendingEnabled(bool enabled);
        void SetBlendingMode(const BlendingMode blendingMode);
        void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, uint32_t elementCount);
    };
}
