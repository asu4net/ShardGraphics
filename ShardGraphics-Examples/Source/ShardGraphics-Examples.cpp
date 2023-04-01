#include <ShardGraphics.h>

using namespace Shard::Graphics;
using namespace Shard;

int main()
{
    const auto window = InstantiateWindow();
    window->Create();
    ImGuiRenderer imGuiRenderer;
    imGuiRenderer.Create(window);

    imGuiRenderer.PushWidget("Test Widget").lock()->UpdateEvent().Add([]()
    {
       ImGui::Button("My button"); 
    });
    
    while (window->KeepOpened())
    {
        Renderer2D::ClearColor(window->GetBackgroundColor());
        imGuiRenderer.Update();
        window->Update();
    }
    
    window->Destroy();
}