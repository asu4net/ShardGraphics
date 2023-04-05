#include "Renderer2D.h"
#include <glad/glad.h>

namespace Shard::Graphics
{
    void Renderer2D::Initialize()
    {
    }
    
    void Renderer2D::ClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer2D::DrawIndices(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }
}
