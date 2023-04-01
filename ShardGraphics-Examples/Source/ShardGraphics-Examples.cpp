#include <ShardGraphics.h>

using namespace Shard::Graphics;
using namespace Shard;

int main()
{
    const auto window = Window::Create();
    window->Initialize();
    
    ImGuiRenderer& imGuiRenderer = ImGuiRenderer::CreateSingleton();
    imGuiRenderer.Initialize(window);

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

    imGuiRenderer.Finalize();
    ImGuiRenderer::DestroySingleton();
    
    window->Finalize();
}