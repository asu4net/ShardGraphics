#include "Context.h"
#include <cassert>
#include "glad/glad.h"
#include <glfw/glfw3.h>

namespace Shard::Graphics
{
#ifdef SH_DEBUG
    static void APIENTRY OnDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity,
            GLsizei length, const char* message, const void* userParam)
    {
        if (!Context::EnableDebugMessages) return;
        Context::OnDebugMessage(message);
    }
#endif

    static GLFWwindow* GetGlfWwindow(void* windowHandler)
    {
        static GLFWwindow* glfWwindowHandler = static_cast<GLFWwindow*>(windowHandler);
        return glfWwindowHandler;
    }
    
    std::shared_ptr<Context> InstantiateContext(void* windowHandler)
    {
        return std::make_shared<Context>(windowHandler);
    }

    Context::Context(void* windowHandler)
        : m_windowHandler(windowHandler)
    {
    }

    void Context::Initialize()
    {
        assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) && "Failed to initialize glad!");
        
#ifdef SH_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OnDebugMessageCallback, nullptr);
#endif
    }

    void Context::SwapBuffers()
    {
        glfwSwapBuffers(GetGlfWwindow(m_windowHandler));
    }

    void Context::SetViewport(const int width, const int height)
    {
        glViewport(0, 0, width, height);
    }
}
