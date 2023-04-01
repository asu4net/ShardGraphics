#pragma once
#include <memory>
#include <string>
#include "WindowEvents.h"
#include "Maths.h"

//TODO: Add controller support
//TODO: Add window icon support

namespace Shard::Graphics
{
    class Context;
    
    class Window
    {
    public:
        enum class CursorMode { Normal, Disabled, Hidden, Captured };
        
        struct Configuration
        {
            std::string title{"Shard Window"};
            int width{1280}, height{720};
            glm::vec4 color{glm::colors::greyColor};
            int openglMajorVersion{4}, openglMinorVersion{6};
            bool vSync{true};
            CursorMode cursorMode{CursorMode::Normal};
        };
        
        virtual ~Window() = default;
        
        static std::shared_ptr<Window> Create();
        
        virtual void Initialize(const Configuration& config = {});
        virtual void Finalize();
        
        virtual void Update();
        
        virtual WindowEvents& Events() { return m_events; }
        virtual void Close() { m_keepWindowOpened = false; }
        virtual bool KeepOpened();
        
        virtual void SetVSync(bool enabled);
        virtual bool IsVSync() const { return m_config.vSync; }

        virtual void SetTitle(const std::string& title);
        virtual const std::string& GetTitle() const { return m_config.title; }
        
        virtual void SetCursorMode(const CursorMode mode);
        virtual CursorMode GetCursorMode() const { return m_config.cursorMode; }
        
        virtual void SetBackgroundColor(const glm::vec4& color) { m_config.color = color; }
        virtual glm::vec4 GetBackgroundColor() const { return m_config.color; }
        
        virtual float GetWidth() const { return static_cast<float>(m_config.width); }
        virtual float GetHeight() const { return static_cast<float>(m_config.height); }
        virtual float GetAspect() const { return GetWidth() / GetHeight(); }

        void* GetHandler() const { return m_windowHandler; }
        
    private:
        std::shared_ptr<Context> m_context;
        WindowEvents m_events;
        GLFWwindow* m_windowHandler = nullptr;    
        Configuration m_config;
        bool m_created = false;
        bool m_keepWindowOpened = true;

        virtual void SetWindowCallbacks();
    };
}