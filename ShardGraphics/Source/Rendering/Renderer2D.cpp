#include "Renderer2D.h"
#include "glad/glad.h"

void Shard::Graphics::Renderer2D::ClearColor(const glm::vec4& clearColor)
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}