#pragma once
#include "Math/Math.h"

namespace Shard::Graphics
{
    class ViewportCamera
    {
    public:
        enum class Projection { None, Perspective, Orthographic };
        
        Projection CurrentProjection;
        float Size;
        float Fov;
        float NearPlane;
        float FarPlane;
        float AspectRatio;
        glm::vec3 Position;
        glm::quat Rotation;
        float MoveSpeed;
        
        ViewportCamera(Projection startProjection = Projection::Perspective);

        glm::mat4 ProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
        
        void UpdateMatrix();
        void Update(float deltaTime);

        void CalculateView(glm::mat4& viewMatrix);
        void CalculatePerspectiveProjection(glm::mat4& projectionMatrix);
        void CalculateOrthographicProjection(glm::mat4& projectionMatrix);
        
    private:
        glm::mat4 m_ProjectionViewMatrix;
    };
}