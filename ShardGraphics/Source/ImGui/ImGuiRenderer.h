#pragma once
#include <memory>
#include <vector>
#include "ImGuiWidget.h"

namespace Shard::Graphics
{
    class Window;
    
    class ImGuiRenderer
    {
    public:
        ImGuiConfigFlags configFlags;
        
        ImGuiRenderer();
        
        template<typename T, typename ...TArgs>
        std::weak_ptr<T> PushWidget(TArgs&& ...args)
        {
            std::shared_ptr<T> widget = std::make_shared<T>(std::forward<TArgs>(args)...);
            m_widgets.push_back(widget);
            widget->OnCreate();
            return widget;
        }

        template<typename ...TArgs>
        std::weak_ptr<ImGuiWidget> PushWidget(TArgs&& ...args)
        {
            return PushWidget<ImGuiWidget>(std::forward<TArgs>(args)...);
        }

        //TODO PopWidget
        void PopWidget(const std::weak_ptr<ImGuiWidget>& widget)
        {
            
        }
        
        void Create(const std::shared_ptr<Window>& window);
        void Update();
        void Destroy();
        
    private:
        std::weak_ptr<Window> m_window;
        std::vector<std::shared_ptr<ImGuiWidget>> m_widgets;
    };
}
