#pragma once
#include <memory>
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
        
        ImGuiWidget(const char* name = "ImGuiWidget", bool* opened = nullptr, ImGuiWindowFlags flags = 0);
        
        virtual ~ImGuiWidget() = default; 
        
        const char* GetName() const { return m_name; }
        
        Delegate<void(ImGuiWidget*)> GetBeginDelegate() const { return m_beginDelegate; }
        Delegate<void()> GetEndDelegate() const { return m_endDelegate; }

        void SetBeginDelegate(const Delegate<void(ImGuiWidget*)>& beginDelegate) { m_beginDelegate = beginDelegate; }
        void SetEndDelegate(const Delegate<void()>& endDelegate) { m_endDelegate = endDelegate; }
        
        void ClearBeginEndDelegates();
        
        FWidgetCreateEvent& CreateEvent() { return m_widgetCreateEvent; }
        FWidgetUpdateEvent& UpdateEvent() { return m_widgetUpdateEvent; }
        FWidgetDestroyEvent& DestroyEvent() { return m_widgetDestroyEvent; }

        void Create();
        void Update();
        void Destroy();
        
        template<typename T, typename ...TArgs>
        std::shared_ptr<T> PushWidget(TArgs&& ...args)
        {
            std::shared_ptr<T> widget = std::make_shared<T>(std::forward<TArgs>(args)...);
            m_childWidgets.push_back(widget);
            widget->Create();
            return widget;
        }
        
        template<typename ...TArgs>
        std::shared_ptr<ImGuiWidget> PushWidget(TArgs&& ...args)
        {
            return PushWidget<ImGuiWidget>(std::forward<TArgs>(args)...);
        }
        
    protected:
        virtual void OnCreate();
        virtual void OnUpdate();
        virtual void OnDestroy();
    
    private:
        const char* m_name;
        Delegate<void(ImGuiWidget*)> m_beginDelegate;
        Delegate<void()> m_endDelegate;
        FWidgetCreateEvent m_widgetCreateEvent;
        FWidgetUpdateEvent m_widgetUpdateEvent;
        FWidgetDestroyEvent m_widgetDestroyEvent;
        std::vector<std::shared_ptr<ImGuiWidget>> m_childWidgets;
    };
}