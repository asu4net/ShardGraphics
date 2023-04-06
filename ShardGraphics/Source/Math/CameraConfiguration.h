#pragma once
#include "glm/glm.hpp"
#include "Transform.h"

enum class Projection { Perspective, Orthographic };

struct CameraConfiguration
{
    Projection Projection = Projection::Orthographic;
    float Size = 3.f;
    float Fov = 85.f;
    float NearPlane = -100.f;
    float FarPlane = 100.f;

    glm::mat4 CalculateViewMatrix(const Transform& transform) const
    {
       return glm::lookAt(transform.Position, (transform.Position - transform.Forward()), transform.Up());
    }

    glm::mat4 CalculateProjectionMatrix(const float aspectRatio) const
    {
        switch (Projection)
        {
        case Projection::Perspective: 
            return glm::perspective(glm::radians(Fov), aspectRatio, 0.f, FarPlane);
        case Projection::Orthographic:
            {
                const float aspect = aspectRatio;
                const float right = aspect * Size; //update aspect ratio
                const float left = -right;
                return glm::ortho(left, right, -Size, Size, NearPlane, FarPlane);
            }
        default:
            return glm::IdentityMatrix;
        }
    }
};