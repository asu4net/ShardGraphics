#include "ImGuiWidget.h"

namespace Shard::Graphics
{
    ImGuiWidget::ImGuiWidget(const char* name, bool* opened, const ImGuiWindowFlags flags, const bool dockSpaceWidget)
        : flags(flags)
        , opened(opened)
        , enabled(true)
        , m_name(name)
        , m_dockSpaceWidget(dockSpaceWidget)
    {
    }

    void ImGuiWidget::OnCreate()
    {
        m_widgetCreateEvent.Broadcast();
    }

    void ImGuiWidget::OnUpdate()
    {
        m_widgetUpdateEvent.Broadcast();
    }

    void ImGuiWidget::OnDestroy()
    {
        m_widgetDestroyEvent.Broadcast();
        m_widgetUpdateEvent.RemoveAll();
    }
}
