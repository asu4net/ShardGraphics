#pragma once
#include "ImGui/ImGuiWidget.h"

namespace Shard::Graphics
{
    class DockSpaceWidget : public ImGuiWidget
    {
    public:
        void OnUpdate() override;
    };
}