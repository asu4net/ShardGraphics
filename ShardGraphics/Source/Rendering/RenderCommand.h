#pragma once
#include "RendererAPI.h"
#include "Data/VertexArray.h"
#include "Data/Shader.h"
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

    class SetUniformCommand : public RenderCommand
    {
    public:
        
        SetUniformCommand(const std::shared_ptr<Shader>& shader, const char* uniformName)
            : RenderCommand()
            , m_Shader(shader)
            , m_UniformName(uniformName)
        {}
        
        void Execute() override
        {
            m_Shader->Bind();
        }

    protected:
        const std::shared_ptr<Shader> m_Shader;
        const char* m_UniformName;
    };
    
    class SetUniformMat4Command : public SetUniformCommand
    {
    public:
        
        SetUniformMat4Command(const std::shared_ptr<Shader>& shader, const char* uniformName, const glm::mat4& mat)
            : SetUniformCommand(shader, uniformName)
            , m_Mat(mat)
        {}

        const char* GetName() const override { return "SetUniformMat4"; }
        
        void Execute() override
        {
            SetUniformCommand::Execute();
            m_Shader->SetUniformMat4(m_UniformName, m_Mat);
        }

    private:
        const glm::mat4 m_Mat;
    };
    
    class SetUniformVec4Command : public SetUniformCommand
    {
    public:
        
        SetUniformVec4Command(const std::shared_ptr<Shader>& shader, const char* uniformName, const glm::vec4& vec)
            : SetUniformCommand(shader, uniformName)
            , m_Vec4(vec)
        {}

        const char* GetName() const override { return "SetUniformVec4"; }
        
        void Execute() override
        {
            SetUniformCommand::Execute();
            m_Shader->SetUniformVec4(m_UniformName, m_Vec4);
        }

    private:
        const glm::vec4 m_Vec4;
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
