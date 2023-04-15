#include "GraphicApplication.h"

namespace Shard::Graphics
{
    GraphicApplication::GraphicApplication()
        : m_Window(Window::CreateAndInitialize())
        , Renderer2D(Renderer2D::CreateAndInitialize(m_Window))
        , ImGuiRenderer(ImGuiRenderer::CreateAndInitialize(m_Window))
        , m_ViewportCamera(std::make_shared<ViewportCamera>())
        , m_LastFrameTime(Time::GetTime())
    {
    }

    GraphicApplication::~GraphicApplication()
    {
        Renderer2D::FinalizeAndDestroy();
        ImGuiRenderer::FinalizeAndDestroy();
        m_Window->Finalize();
    }

    void GraphicApplication::Create()
    {
        m_RootWidget = ImGuiRenderer::GetInstance().CreateRootWidget<ImGuiWidget>("Settings:");
        OnCreate();
        
        while (m_Window->KeepOpened())
        {
            const double time = Time::GetTime();
            const float deltaTime = static_cast<float>(time - m_LastFrameTime);
            m_LastFrameTime = time;
            Update(deltaTime);
        }
    }

    void GraphicApplication::Update(const float deltaTime)
    {
        m_Window->PollEvents();
        Renderer2D.ClearScreen();
        m_ViewportCamera->AspectRatio = m_Window->GetAspect();
        m_ViewportCamera->Update(deltaTime);
        Renderer2D.Begin(m_ViewportCamera->ProjectionViewMatrix());
        OnUpdate(deltaTime);
        Renderer2D.End();
        ImGuiRenderer.DrawWidgets();
        m_Window->SwapBuffers();
    }
}
