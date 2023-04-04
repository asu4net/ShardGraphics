#include "ImGuiWidget.h"

namespace Shard::Graphics
{
    ImGuiWidget::ImGuiWidget(const char* name, bool* opened, const ImGuiWindowFlags flags)
        : flags(flags)
        , opened(opened)
        , enabled(true)
        , m_name(name)
    {
        m_beginDelegate = {[](const ImGuiWidget* widget)
        {
            ImGui::Begin(widget->GetName(), widget->opened, widget->flags);
        }};
        m_endDelegate = {[&](){ ImGui::End(); }};
    }

    void ImGuiWidget::ClearBeginEndDelegates()
    {
        m_beginDelegate.Clear();
        m_endDelegate.Clear();
    }

    void ImGuiWidget::Create()
    {
        OnCreate();
        m_widgetCreateEvent.Broadcast();
    }

    void ImGuiWidget::Update()
    {
        if (!enabled) return;
        m_beginDelegate(this);
        OnUpdate();
        m_widgetUpdateEvent.Broadcast();
        for (const auto& child : m_childWidgets)
            child->Update();
        m_endDelegate();
    }
    
    void ImGuiWidget::Destroy()
    {
        OnDestroy();
        ClearBeginEndDelegates();
        m_widgetDestroyEvent.Broadcast();
        m_widgetUpdateEvent.RemoveAll();
    }

    void ImGuiWidget::OnCreate() {}
    void ImGuiWidget::OnUpdate() {}
    void ImGuiWidget::OnDestroy() {}
}