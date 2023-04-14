#include <ShardGraphics.h>
#include "ImGui/Widgets/Vector3Widget.h"
#include "Rendering/ViewportCamera.h"
#include "Rendering/Data/Texture2D.h"
#include "Window/Time/Time.h"

using namespace Shard::Graphics;
using namespace Shard;

int main()
{
    const auto window = Window::CreateAndInitialize();
    Renderer2D& renderer2D = Renderer2D::CreateAndInitialize(window);
    ImGuiRenderer& imGuiRenderer = ImGuiRenderer::CreateAndInitialize(window);
    
    ViewportCamera viewPortCamera;
    
    glm::vec3 trianglePosition = Global::RightVector * 2.f;
    const auto rootWidget = imGuiRenderer.CreateRootWidget<ImGuiWidget>("Settings");
    Vector3Widget widget(trianglePosition, "Position");
    rootWidget->PushWidget<Vector3Widget>(widget);

    double lastFrameTime = Time::GetTime();
    const auto texture1 = Texture2D::Create("Content/Textures/Checkerboard.png");
    const auto texture2 = Texture2D::Create("Content/Textures/bola.jpg");
    
    while (window->KeepOpened())
    {
        window->PollEvents();
        renderer2D.ClearScreen();

        const double time = Time::GetTime();
        const float deltaTime = static_cast<float>(time - lastFrameTime);
        lastFrameTime = time;
        
        viewPortCamera.Update(deltaTime);
        
        renderer2D.Begin(viewPortCamera.ProjectionViewMatrix());
        renderer2D.SubmitPrimitive(PrimitiveType::Triangle, glm::translate(Global::IdentityMatrix, trianglePosition));
        renderer2D.SubmitPrimitive(PrimitiveType::Quad, glm::translate(Global::IdentityMatrix, {0, 1, 0}),
            Global::YellowColor);
        renderer2D.SubmitPrimitive(PrimitiveType::Quad, glm::translate(Global::IdentityMatrix, {0, 0, 0}),
            Global::WhiteColor, texture1);
        renderer2D.SubmitPrimitive(PrimitiveType::Quad, glm::translate(Global::IdentityMatrix, {1, 0, 0}),
           Global::WhiteColor,  texture2);
        renderer2D.End();
        
        imGuiRenderer.DrawWidgets();
        window->SwapBuffers();
    }

    ImGuiRenderer::FinalizeAndDestroy();
    Renderer2D::FinalizeAndDestroy();
    window->Finalize();
}