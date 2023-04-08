#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Math/Transform.h"
#include "CameraController.h"

namespace Shard::Graphics
{
    class Camera
    {
    public:
        enum class Projection { None, Perspective, Orthographic };
        
        Projection CurrentProjection;
        Transform ViewTransform;
        float Size;
        float Fov;
        float NearPlane;
        float FarPlane;
        float AspectRatio;
        
        Camera(Projection startProjection = Projection::Perspective);

        glm::mat4 ProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

        template<typename T>
        std::shared_ptr<T> AttachController()
        {
            DetachController();
            auto controller = std::make_shared<T>(this);
            m_Controller = controller;
            m_Controller->Attach();
            return controller;
        }

        void DetachController();
        
        template<typename T>
        std::shared_ptr<T> GetController()
        {
            return static_cast<T>(m_Controller);
        }
        
        void UpdateMatrix();
        void Update(float deltaTime);

        void CalculateView(glm::mat4& viewMatrix);
        void CalculatePerspectiveProjection(glm::mat4& projectionMatrix);
        void CalculateOrthographicProjection(glm::mat4& projectionMatrix);
        
    private:
        std::shared_ptr<CameraController> m_Controller;
        glm::mat4 m_ProjectionViewMatrix;
    };
}