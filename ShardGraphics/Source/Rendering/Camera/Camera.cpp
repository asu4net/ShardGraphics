#include "Camera.h"

namespace Shard::Graphics
{
    Camera::Camera(const Projection startProjection)
        : CurrentProjection(startProjection)
        , Size(3.f)
        , Fov(85.f)
        , NearPlane(0.1f)
        , FarPlane(1000.f)
        , AspectRatio(1280.f / 720.f)
        , Position(Global::ForwardVector * -2.f)
        , Rotation(Global::IdentityMatrix)
        , m_ProjectionViewMatrix(Global::IdentityMatrix)
    {
    }

    void Camera::DetachController()
    {
        if (m_Controller)
            m_Controller->Detach();
        m_Controller.reset();
    }

    void Camera::UpdateMatrix()
    {
        glm::mat4 viewMatrix = Global::IdentityMatrix;
        CalculateView(viewMatrix);

        glm::mat4 projectionMatrix = Global::IdentityMatrix;
        switch (CurrentProjection)
        {
        case Projection::Perspective: CalculatePerspectiveProjection(projectionMatrix); break;
        case Projection::Orthographic: CalculateOrthographicProjection(projectionMatrix); break;
        case Projection::None: projectionMatrix = Global::IdentityMatrix; break;
        }

        m_ProjectionViewMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::Update(const float deltaTime)
    {
        UpdateMatrix();
        if (m_Controller)
            m_Controller->Update(deltaTime);
    }

    void Camera::CalculateView(glm::mat4& viewMatrix)
    {
        glm::vec3 tweakedPosition = Position;
        tweakedPosition.z *= -1;
        viewMatrix = glm::translate(glm::mat4(1.0f), tweakedPosition) * glm::toMat4(Rotation);
        viewMatrix = glm::inverse(viewMatrix);
    }

    void Camera::CalculatePerspectiveProjection(glm::mat4& projectionMatrix)
    {
        projectionMatrix = glm::perspective(glm::radians(Fov), AspectRatio,
            NearPlane, FarPlane);
    }

    void Camera::CalculateOrthographicProjection(glm::mat4& projectionMatrix)
    {
        const float right = AspectRatio * Size; //update aspect ratio
        const float left = -right;
        projectionMatrix = glm::ortho(left, right, -Size, Size, NearPlane, FarPlane);
    }
}