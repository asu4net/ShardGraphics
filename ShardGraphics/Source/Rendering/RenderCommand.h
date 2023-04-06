#pragma once
#include "RendererAPI.h"
#include "Data/VertexArray.h"
#include <memory>

namespace Shard::Graphics
{
    class RenderCommand
    {
    public:
        RenderCommand();

        virtual const char* GetName() const = 0;
        virtual void Execute() = 0;
        
    protected:
        const std::unique_ptr<RendererAPI>& GetRendererAPI() const { return m_RendererAPI; }
    
    private:
        std::unique_ptr<RendererAPI> m_RendererAPI; 
    };
    
    class SetViewPortCommand : public RenderCommand
    {
    public:
        SetViewPortCommand(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
            : RenderCommand(), m_X(x), m_Y(y), m_Width(width), m_Height(height)
        {}

        const char* GetName() const override { return "SetViewport"; }
        
        void Execute() override
        {
            GetRendererAPI()->SetViewport(m_X, m_Y, m_Width, m_Height);
        }

    private:
        uint32_t m_X, m_Y, m_Width, m_Height; 
    };

    class SetClearColorCommand : public RenderCommand
    {
    public:
        SetClearColorCommand(const glm::vec4& clearColor)
            : RenderCommand()
            , m_ClearColor(clearColor)
        {}

        const char* GetName() const override { return "SetClearColor"; }

        void Execute() override
        {
            GetRendererAPI()->SetClearColor(m_ClearColor);
        }

    private:
        glm::vec4 m_ClearColor;
    };

    class ClearCommand : public RenderCommand
    {
    public:

        const char* GetName() const override { return "Clear"; }
        
        void Execute() override
        {
            GetRendererAPI()->Clear();
        }
    };

    class DrawElementsCommand : public RenderCommand
    {
    public:
        DrawElementsCommand(const std::shared_ptr<VertexArray>& vertexArray)
            : RenderCommand()
            , m_VertexArray(vertexArray)
        {}

        const char* GetName() const override { return "DrawElements"; }
        
        void Execute() override
        {
            GetRendererAPI()->DrawElements(m_VertexArray);
        }

    private:
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}