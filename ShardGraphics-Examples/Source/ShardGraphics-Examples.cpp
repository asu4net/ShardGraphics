#include <ShardGraphics.h>
#include "ImGui/Widgets/Vector3Widget.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Camera/Controllers/ViewportCameraController.h"

using namespace Shard::Graphics;
using namespace Shard;

int main()
{
    const auto window = Window::CreateAndInitialize();
    Renderer2D& renderer2D = Renderer2D::CreateAndInitialize(window);
    ImGuiRenderer& imGuiRenderer = ImGuiRenderer::CreateAndInitialize(window);
    
    Camera viewPortCamera;
    viewPortCamera.AttachController<ViewportCameraController>();
    
    Transform triangleTransform = {{2, 0 ,0}};
    const auto rootWidget = imGuiRenderer.CreateRootWidget<ImGuiWidget>("Settings");
    Vector3Widget widget(triangleTransform.Position, "Position");
    rootWidget->PushWidget<Vector3Widget>(widget);

    double lastFrameTime = window->GetTime();
    
    while (window->KeepOpened())
    {
        window->PollEvents();
        renderer2D.ClearScreen();

        double time = window->GetTime();
        float deltaTime = static_cast<float>(time - lastFrameTime);
        lastFrameTime = time;
        
        viewPortCamera.Update(deltaTime);
        
        renderer2D.Begin(viewPortCamera);
        renderer2D.SubmitPrimitive(PrimitiveType::Triangle, triangleTransform);
        renderer2D.SubmitPrimitive(PrimitiveType::Triangle);
        renderer2D.DrawPrimitives();
        
        imGuiRenderer.DrawWidgets();
        window->SwapBuffers();
    }

    ImGuiRenderer::FinalizeAndDestroy();
    Renderer2D::FinalizeAndDestroy();
    window->Finalize();
}