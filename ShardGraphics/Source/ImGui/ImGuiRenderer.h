#pragma once
#include <memory>
#include <vector>
#include "ImGuiWidget.h"
#include <ShardCore.h>

namespace Shard::Graphics
{
    class Window;
    
    class ImGuiRenderer : public Singleton<ImGuiRenderer>
    {
    public:
        ImGuiConfigFlags ConfigFlags;
        
        ImGuiRenderer();
        ImGuiRenderer(ImGuiRenderer&& other) = delete;
        
        template<typename T, typename ...TArgs>
        std::shared_ptr<T> CreateRootWidget(TArgs&& ...args)
        {
            if (m_RootWidget)
                DestroyRootWidget();
            std::shared_ptr<T> widget = std::make_shared<T>(std::forward<TArgs>(args)...);
            m_RootWidget = widget;
            widget->Create();
            return widget;
        }
        
        template<typename ...TArgs>
        std::shared_ptr<ImGuiWidget> CreateRootWidget(TArgs&& ...args)
        {
            return CreateRootWidget<ImGuiWidget>(std::forward<TArgs>(args)...);
        }

        void DestroyRootWidget();
        
        void Initialize(const std::shared_ptr<Window>& window);
        void Update();
        void Finalize();
        
    private:
        std::weak_ptr<Window> m_Window;
        std::shared_ptr<ImGuiWidget> m_RootWidget;
    };
}
