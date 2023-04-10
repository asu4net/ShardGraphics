#include "ViewportCameraController.h"
#include "Rendering/Camera/Camera.h"
#include "Window/Window.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"

namespace Shard::Graphics
{
    ViewportCameraController::ViewportCameraController(Camera* camera)
            : CameraController(camera)
            , m_MoveSpeed(2.f)
    {
    }
    
    void ViewportCameraController::OnUpdate(const float deltaTime)
    {
        glm::vec3& position = GetCamera()->Position;
        const float displacement = m_MoveSpeed * deltaTime;
       
        if (Input::IsKeyPressed(KEY_S))
            position.z -= displacement;
        if (Input::IsKeyPressed(KEY_W))
            position.z += displacement;
            
        if (Input::IsKeyPressed(KEY_A))
            position.x -= displacement;
        if (Input::IsKeyPressed(KEY_D))
            position.x += displacement;

        if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            position.y -= displacement;
        if (Input::IsKeyPressed(KEY_SPACE))
            position.y += displacement;
    }
}
