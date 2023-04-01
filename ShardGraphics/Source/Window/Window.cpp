#include "Window.h"
#include <glfw/glfw3.h>
#include "Rendering/Context.h"

namespace Shard::Graphics
{
    void Window::Update()
    {
        glfwPollEvents();
        m_context->SwapBuffers();
    }

    std::shared_ptr<Window> Window::Create()
    {
        return std::make_shared<Window>();
    }

    void Window::Initialize(const Configuration& config)
    {
        assert(!m_created && "Window already created!");
        Events().CallBeginInitializeEvent();
        m_config = config;
        
        assert(glfwInit() && "GLFW initialisation failed!");
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_config.openglMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_config.openglMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        
        m_windowHandler = glfwCreateWindow(m_config.width, m_config.height, m_config.title.c_str(), nullptr, nullptr);
        assert(m_windowHandler && "Window creation failed!");
        
        m_context = InstantiateContext(m_windowHandler);
        glfwMakeContextCurrent(m_windowHandler);
        
        m_context->Initialize();
        
        SetVSync(config.vSync);
        m_context->SetViewport(m_config.width, m_config.height);

        Events().resizeEvent.Add([&](const int width, const int height)
        {
            m_config.width = width;
            m_config.height = height;
        });
        
        SetWindowCallbacks();
        
        Events().CallEndInitializeEvent();
        m_created = true;
    }
    
    void Window::Finalize()
    {
        Events().CallBeginFinalizeEvent();
        assert(m_created && "You're trying to destroy an uncreated window!");
        glfwDestroyWindow(m_windowHandler);
        m_created = false;
        Events().CallEndFinalizeEvent();
    }

    bool Window::KeepOpened()
    {
        return !glfwWindowShouldClose(m_windowHandler) && m_keepWindowOpened;
    }

    void Window::SetVSync(const bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_config.vSync = enabled;
    }

    void Window::SetTitle(const std::string& title)
    {
        m_config.title = title;
        glfwSetWindowTitle(m_windowHandler, title.c_str());
    }
    
    void Window::SetCursorMode(const CursorMode mode)
    {
        m_config.cursorMode = mode;
		
        switch (m_config.cursorMode)
        {
        case CursorMode::Normal:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            return;
        case CursorMode::Disabled:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            return;
        case CursorMode::Hidden:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            return;
        case CursorMode::Captured:
            glfwSetInputMode(m_windowHandler, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
        }
    }
    
    //---------------------------------------------------------
    // GLFW CALLBACKS
    //---------------------------------------------------------
    
    static WindowEvents& GetEvents(GLFWwindow* windowHandler)
    {
        static WindowEvents* events = static_cast<WindowEvents*>(glfwGetWindowUserPointer(windowHandler));
        return *events;
    }
    
    void WindowSizeCallback(GLFWwindow* windowHandler, const int width, const int height) { GetEvents(windowHandler).CallResizeEvent(width, height); }
    void WindowCloseCallback(GLFWwindow* windowHandler) { GetEvents(windowHandler).CallCloseEvent(); }
    void WindowKeyPressedCallback(GLFWwindow* windowHandler, const int key, const bool pressed) { GetEvents(windowHandler).CallKeyPressedEvent(key, pressed); }
    void WindowKeyReleasedCallback(GLFWwindow* windowHandler, const int key) { GetEvents(windowHandler).CallKeyReleasedEvent(key); }
    void WindowCursorPosCallback(GLFWwindow* windowHandler, const glm::vec2& pos) { GetEvents(windowHandler).CallCursorPosEvent(pos); }
    void WindowMouseButtonPressedCallback(GLFWwindow* windowHandler, const int mouseButton, const bool pressed) { GetEvents(windowHandler).CallMouseButtonPressedEvent(mouseButton, pressed); }
    void WindowMouseButtonReleasedCallback(GLFWwindow* windowHandler, const int mouseButton) { GetEvents(windowHandler).CallMouseButtonReleasedEvent(mouseButton); }
    void WindowScrollCallback(GLFWwindow* windowHandler, const glm::vec2& offset) { GetEvents(windowHandler).CallScrollEvent(offset); }

    void Window::SetWindowCallbacks()
    {
        glfwSetWindowUserPointer(m_windowHandler, &m_events);
        
        glfwSetWindowSizeCallback(m_windowHandler, WindowSizeCallback);
        glfwSetWindowCloseCallback(m_windowHandler, WindowCloseCallback);
        glfwSetKeyCallback(m_windowHandler, [](GLFWwindow* windowHandler, const int key, const int scanCode, const int action, const int mods)
        {
            switch (action)
            {
            case GLFW_PRESS:
                WindowKeyPressedCallback(windowHandler, key, false);
                return;
            case GLFW_RELEASE:
                WindowKeyReleasedCallback(windowHandler, key);
                return;
            case GLFW_REPEAT:
                WindowKeyPressedCallback(windowHandler, key, true);
            }
        });
        glfwSetCursorPosCallback(m_windowHandler, [](GLFWwindow* windowHandler, const double xPos, const double yPos)
        {
            const glm::vec2 cursorPosition = {static_cast<float>(xPos), static_cast<float>(yPos)};
            WindowCursorPosCallback(windowHandler, cursorPosition);
        });
        glfwSetMouseButtonCallback(m_windowHandler, [](GLFWwindow* windowHandler, const int button, const int action, const int mods)
        {
            switch (action)
            {
            case GLFW_PRESS:
                WindowMouseButtonPressedCallback(windowHandler, button, false);
                return;
            case GLFW_RELEASE:
                WindowMouseButtonReleasedCallback(windowHandler, button);
                return;
            case GLFW_REPEAT:
                WindowMouseButtonPressedCallback(windowHandler, button, true);
            }
        });
        glfwSetScrollCallback(m_windowHandler, [](GLFWwindow* windowHandler, const double xOffset, const double yOffset)
        {
            const glm::vec2 offset = {static_cast<float>(xOffset), static_cast<float>(yOffset)};
            WindowScrollCallback(windowHandler, offset);
        });
    }

    // ---------------------------------------------------------
}