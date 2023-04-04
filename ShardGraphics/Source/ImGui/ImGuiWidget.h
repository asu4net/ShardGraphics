#pragma once
#include "imgui.h"
#include "Delegates/MulticastDelegate.h"

namespace Shard::Graphics
{
    DECLARE_EVENT(class ImGuiWidget, FWidgetCreateEvent)
    DECLARE_EVENT(class ImGuiWidget, FWidgetUpdateEvent)
    DECLARE_EVENT(class ImGuiWidget, FWidgetDestroyEvent)
    
    class ImGuiWidget
    {
    public:
        ImGuiWindowFlags flags;
        bool* opened;
        bool enabled;
        
        ImGuiWidget(const char* name = "ImGuiWidget",  bool* opened = nullptr, ImGuiWindowFlags flags = 0, bool dockSpaceWidget = true);
        
        virtual ~ImGuiWidget() = default; 
        
        const char* GetName() const { return m_name; }
        bool IsInDockSpace() const { return m_dockSpaceWidget; }
        
        FWidgetCreateEvent& CreateEvent() { return m_widgetCreateEvent; }
        FWidgetUpdateEvent& UpdateEvent() { return m_widgetUpdateEvent; }
        FWidgetDestroyEvent& DestroyEvent() { return m_widgetDestroyEvent; }
        
        virtual void OnCreate();
        virtual void OnUpdate();
        virtual void OnDestroy();
    
    private:
        FWidgetCreateEvent m_widgetCreateEvent;
        FWidgetUpdateEvent m_widgetUpdateEvent;
        FWidgetDestroyEvent m_widgetDestroyEvent;
        const char* m_name;
        const bool m_dockSpaceWidget;
    };
}
