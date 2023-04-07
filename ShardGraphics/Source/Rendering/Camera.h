#pragma once
#include <glm/glm.hpp>
#include "Math/Transform.h"

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

        void UpdateMatrix();

        void CalculateView(glm::mat4& viewMatrix);
        void CalculatePerspectiveProjection(glm::mat4& projectionMatrix);
        void CalculateOrthographicProjection(glm::mat4& projectionMatrix);
        
    private:
        glm::mat4 m_ProjectionViewMatrix;
    };
}