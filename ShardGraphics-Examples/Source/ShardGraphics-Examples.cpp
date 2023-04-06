#include <ShardGraphics.h>

using namespace Shard::Graphics;
using namespace Shard;

int main()
{
    const std::shared_ptr<Window> window(Window::Create());
    window->Initialize();
    
    Renderer2D& renderer2D = Renderer2D::CreateSingleton();
    renderer2D.Initialize();
    renderer2D.SetViewPort(0, 0, window->GetWidth(), window->GetHeight());
    
    ImGuiRenderer& imGuiRenderer = ImGuiRenderer::CreateSingleton();
    imGuiRenderer.Initialize(window);
    
    imGuiRenderer.CreateRootWidget("Test Widget")->UpdateEvent().Add([]()
    {
       ImGui::Button("My button"); 
    });
    
    while (window->KeepOpened())
    {
        renderer2D.SetClearColor(window->GetBackgroundColor());
        renderer2D.Clear();
        renderer2D.DrawPrimitive(PrimitiveType::Triangle, {}, glm::LightRedColor);
        renderer2D.Update();
        
        imGuiRenderer.Update();
        window->Update();
    }

    imGuiRenderer.Finalize();
    ImGuiRenderer::DestroySingleton();
    
    renderer2D.Finalize();
    Renderer2D::DestroySingleton();

    window->Finalize();
}