#pragma once
#include "Maths.h"
#include "Utility/Singleton.h"

namespace Shard::Graphics
{
    class Renderer2D : public Singleton<Renderer2D>
    {
    public:
        void Initialize();
        void ClearColor(const glm::vec4& color);
        void DrawIndices(uint32_t count);
    };
}
