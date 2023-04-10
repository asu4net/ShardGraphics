#include "RendererAPI.h"
#include "Data/IndexBuffer.h"
#include "Data/VertexArray.h"
#include <glad/glad.h>

namespace Shard::Graphics
{
    RendererAPI* RendererAPI::Create()
    {
        return new RendererAPI();
    }

    void RendererAPI::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void RendererAPI::SetClearColor(const glm::vec4& clearColor)
    {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void RendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        vertexArray->Unbind();
    }
}