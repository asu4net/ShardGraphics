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
            std::string Title{"Shard Window"};
            int Width{1280}, Height{720};
            glm::vec4 Color{glm::colors::GreyColor};
            int OpenGlMajorVersion{4}, OpenGlMinorVersion{6};
            bool VSync{true};
            CursorMode CursorMode{CursorMode::Normal};
        };
        
        virtual ~Window() = default;
        
        static Window* Create();
        
        virtual void Initialize(const Configuration& config = {});
        virtual void Finalize();
        
        virtual void Update();
        
        virtual WindowEvents& Events() { return m_Events; }
        virtual void Close() { m_KeepWindowOpened = false; }
        virtual bool KeepOpened();
        
        virtual void SetVSync(bool enabled);
        virtual bool IsVSync() const { return m_Config.VSync; }

        virtual void SetTitle(const std::string& title);
        virtual const std::string& GetTitle() const { return m_Config.Title; }
        
        virtual void SetCursorMode(const CursorMode mode);
        virtual CursorMode GetCursorMode() const { return m_Config.CursorMode; }
        
        virtual void SetBackgroundColor(const glm::vec4& color) { m_Config.Color = color; }
        virtual glm::vec4 GetBackgroundColor() const { return m_Config.Color; }
        
        virtual float GetWidth() const { return static_cast<float>(m_Config.Width); }
        virtual float GetHeight() const { return static_cast<float>(m_Config.Height); }
        virtual float GetAspect() const { return GetWidth() / GetHeight(); }

        void* GetHandler() const { return m_WindowHandler; }
        
    private:
        std::shared_ptr<Context> m_Context;
        WindowEvents m_Events;
        GLFWwindow* m_WindowHandler = nullptr;    
        Configuration m_Config;
        bool m_bCreated = false;
        bool m_KeepWindowOpened = true;

        virtual void SetWindowCallbacks();
    };
}