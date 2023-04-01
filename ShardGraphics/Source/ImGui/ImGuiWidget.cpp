#include "ImGuiWidget.h"

namespace Shard::Graphics
{
    ImGuiWidget::ImGuiWidget(const char* name, bool* opened, const ImGuiWindowFlags flags)
        : flags(flags)
        , opened(opened)
        , m_name(name)
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
