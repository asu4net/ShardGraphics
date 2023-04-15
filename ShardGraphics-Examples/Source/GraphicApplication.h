#pragma once
#include <ShardGraphics.h>

namespace Shard::Graphics
{
    class Window;
    class ViewportCamera;
    class ImGuiWidget;
    
    class GraphicApplication
    {
        std::shared_ptr<Window> m_Window;   

    public:
        Renderer2D& Renderer2D;
        ImGuiRenderer& ImGuiRenderer;
        
        GraphicApplication();
        virtual ~GraphicApplication();

        const std::shared_ptr<ViewportCamera>& GetViewportCamera() const { return m_ViewportCamera; }
        const std::shared_ptr<Window>& GetWindow() const { return m_Window; }
        const std::shared_ptr<ImGuiWidget>& GetRootWidget() const { return m_RootWidget; }

        void Create();
        
    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        
    private:
        std::shared_ptr<ViewportCamera> m_ViewportCamera;
        std::shared_ptr<ImGuiWidget> m_RootWidget;
        double m_LastFrameTime;
        
        void Update(float deltaTime);
    };
}