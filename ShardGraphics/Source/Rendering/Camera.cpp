#include "Camera.h"

namespace Shard::Graphics
{
    Camera::Camera(const Projection startProjection)
        : CurrentProjection(startProjection)
        , ViewTransform({glm::ForwardVector * -1.f })
        , Size(3.f)
        , Fov(85.f)
        , NearPlane(0.1f)
        , FarPlane(1000.f)
        , AspectRatio(1280.f / 720.f)
        , m_ProjectionViewMatrix(glm::IdentityMatrix)
    {
    }

    void Camera::UpdateMatrix()
    {
        glm::mat4 viewMatrix = glm::IdentityMatrix;
        CalculateView(viewMatrix);

        glm::mat4 projectionMatrix = glm::IdentityMatrix;
        switch (CurrentProjection)
        {
        case Projection::Perspective: CalculatePerspectiveProjection(projectionMatrix); break;
        case Projection::Orthographic: CalculateOrthographicProjection(projectionMatrix); break;
        case Projection::None: projectionMatrix = glm::IdentityMatrix; break;
        }

        m_ProjectionViewMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::CalculateView(glm::mat4& viewMatrix)
    {
        glm::vec3 position = ViewTransform.Position;
        position.z *= -1;
        viewMatrix = glm::lookAt(position, (position - ViewTransform.Forward()), ViewTransform.Up());
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