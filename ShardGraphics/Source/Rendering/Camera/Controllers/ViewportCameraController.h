#pragma once
#include "Rendering/Camera/CameraController.h"
#include <memory>

namespace Shard::Graphics
{
    class Window;
    
    class ViewportCameraController : public CameraController
    {
    public:
        ViewportCameraController(Camera* camera);

    protected:
        void OnUpdate(float deltaTime) override;

    private:
        float m_MoveSpeed;
    };
}
