#include "CameraController.h"

namespace Shard::Graphics
{
    CameraController::CameraController(Camera* camera)
        : m_Camera(camera)
    {}

    void CameraController::Attach()
    {
        OnAttach();
    }

    void CameraController::Update(const float deltaTime)
    {
        OnUpdate(deltaTime);
    }

    void CameraController::Detach()
    {
        OnDetach();
        m_Camera = nullptr;
    }

    void CameraController::OnAttach() {}
    void CameraController::OnUpdate(float deltaTime) {}
    void CameraController::OnDetach() {}
}
