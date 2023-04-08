#include "ViewportCameraController.h"
#include "Rendering/Camera/Camera.h"
#include "Window/Window.h"
#include "Window/Input/Input.h"
#include "Window/Input/KeyCodes.h"

namespace Shard::Graphics
{
    ViewportCameraController::ViewportCameraController(Camera* camera)
            : CameraController(camera)
            , m_MoveSpeed(2.f)
    {
    }
    
    void ViewportCameraController::OnUpdate(const float deltaTime)
    {
        Transform& camTransform = GetCamera()->ViewTransform;
        const float displacement = m_MoveSpeed * deltaTime;
       
        if (Input::IsKeyPressed(KEY_S))
            camTransform.Position.z -= displacement;
        if (Input::IsKeyPressed(KEY_W))
            camTransform.Position.z += displacement;
            
        if (Input::IsKeyPressed(KEY_A))
            camTransform.Position.x -= displacement;
        if (Input::IsKeyPressed(KEY_D))
            camTransform.Position.x += displacement;

        if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            camTransform.Position.y -= displacement;
        if (Input::IsKeyPressed(KEY_SPACE))
            camTransform.Position.y += displacement;
    }
}
