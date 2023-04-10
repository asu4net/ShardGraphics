﻿#include "ViewportCamera.h"
#include "Window/Input/Input.h"

namespace Shard::Graphics
{
    ViewportCamera::ViewportCamera(const Projection startProjection)
        : CurrentProjection(startProjection)
        , Size(3.f)
        , Fov(85.f)
        , NearPlane(0.1f)
        , FarPlane(1000.f)
        , AspectRatio(1280.f / 720.f)
        , Position(Global::ForwardVector * -2.f)
        , Rotation(Global::IdentityMatrix)
        , MoveSpeed(2.f)
        , m_ProjectionViewMatrix(Global::IdentityMatrix)
    {
    }

    void ViewportCamera::UpdateMatrix()
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

    void ViewportCamera::Update(const float deltaTime)
    {
        UpdateMatrix();
        
        const float displacement = MoveSpeed * deltaTime;
       
        if (Input::IsKeyPressed(KEY_S))
            Position.z -= displacement;
        if (Input::IsKeyPressed(KEY_W))
            Position.z += displacement;
            
        if (Input::IsKeyPressed(KEY_A))
            Position.x -= displacement;
        if (Input::IsKeyPressed(KEY_D))
            Position.x += displacement;

        if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            Position.y -= displacement;
        if (Input::IsKeyPressed(KEY_SPACE))
            Position.y += displacement;
    }

    void ViewportCamera::CalculateView(glm::mat4& viewMatrix)
    {
        glm::vec3 tweakedPosition = Position;
        tweakedPosition.z *= -1;
        viewMatrix = glm::translate(glm::mat4(1.0f), tweakedPosition) * glm::toMat4(Rotation);
        viewMatrix = glm::inverse(viewMatrix);
    }

    void ViewportCamera::CalculatePerspectiveProjection(glm::mat4& projectionMatrix)
    {
        projectionMatrix = glm::perspective(glm::radians(Fov), AspectRatio,
            NearPlane, FarPlane);
    }

    void ViewportCamera::CalculateOrthographicProjection(glm::mat4& projectionMatrix)
    {
        const float right = AspectRatio * Size; //update aspect ratio
        const float left = -right;
        projectionMatrix = glm::ortho(left, right, -Size, Size, NearPlane, FarPlane);
    }
}