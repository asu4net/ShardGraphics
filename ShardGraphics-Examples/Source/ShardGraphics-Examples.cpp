#include <ShardGraphics.h>
#include "Rendering/Camera.h"

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
    
    imGuiRenderer.CreateRootWidget("Camera")->UpdateEvent().Add([]()
    {
       ImGui::Button("My button"); 
    });
    

    Camera camera;
    
    
    bool pause = false;
    
    window->Events().KeyPressedEvent.Add([&](const int key, bool)
    {
        Transform& camTransform = camera.ViewTransform;
        constexpr float camSpeed = 0.06f;
        
        if (key == KEY_LEFT)
            camTransform.Position.x -= camSpeed;
        if (key == KEY_RIGHT)
            camTransform.Position.x += camSpeed;

        if (key == KEY_DOWN)
            camTransform.Position.y -= camSpeed;
        if (key == KEY_UP)
            camTransform.Position.y += camSpeed;

        if (key == KEY_S)
            camTransform.Position.z -= camSpeed;
        if (key == KEY_W)
            camTransform.Position.z += camSpeed;

        if (key == KEY_SPACE)
            pause = !pause;
    });

    Transform triangleTransform;
    
    while (window->KeepOpened())
    {
        window->PollEvents();
        if (pause) continue;

        renderer2D.SetClearColor(window->GetBackgroundColor());
        renderer2D.Clear();

        camera.UpdateMatrix();
        renderer2D.Begin(camera);
        renderer2D.DrawPrimitive(PrimitiveType::Triangle, triangleTransform, glm::LightRedColor);
        
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