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
    
    glm::vec3 trianglePosition = glm::RightVector * 2.f;
    const auto rootWidget = imGuiRenderer.CreateRootWidget<ImGuiWidget>("Settings");
    Vector3Widget widget(trianglePosition, "Position");
    rootWidget->PushWidget<Vector3Widget>(widget);

    double lastFrameTime = window->GetTime();
    
    while (window->KeepOpened())
    {
        window->PollEvents();
        renderer2D.ClearScreen();

        const double time = window->GetTime();
        const float deltaTime = static_cast<float>(time - lastFrameTime);
        lastFrameTime = time;
        
        viewPortCamera.Update(deltaTime);
        
        renderer2D.SetProjectionViewMatrix(viewPortCamera.ProjectionViewMatrix());
        renderer2D.SubmitPrimitive(PrimitiveType::Triangle, glm::translate(glm::IdentityMatrix, trianglePosition));
        renderer2D.SubmitPrimitive(PrimitiveType::Triangle);
        renderer2D.DrawPrimitives();
        
        imGuiRenderer.DrawWidgets();
        window->SwapBuffers();
    }

    ImGuiRenderer::FinalizeAndDestroy();
    Renderer2D::FinalizeAndDestroy();
    window->Finalize();
}