﻿#pragma once
#include <ShardGraphics.h>
#include "Camera/LogicCamera.h"

namespace Shard::Graphics
{
    class Window;
    class Camera;
    class ImGuiWidget;
    
    class GraphicApplication
    {
        std::shared_ptr<Window> m_Window;   

    public:
        Renderer2D& Renderer2D;
        ImGuiRenderer& ImGuiRenderer;
        
        GraphicApplication();
        virtual ~GraphicApplication();

        const std::shared_ptr<LogicCamera>& GetCamera() const { return m_LogicCamera; }
        const std::shared_ptr<Window>& GetWindow() const { return m_Window; }
        const std::shared_ptr<ImGuiWidget>& GetRootWidget() const { return m_RootWidget; }

        void Create();
        
    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        
    private:
        std::shared_ptr<LogicCamera> m_LogicCamera;
        std::shared_ptr<ImGuiWidget> m_RootWidget;
        double m_LastFrameTime;
        
        void Update(float deltaTime);
    };
}
