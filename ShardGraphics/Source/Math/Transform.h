#pragma once
#include "Defaults.h"
#include "Utils.h"
#include "glm/gtx/matrix_decompose.hpp"

struct Transform
{
    glm::vec3 Position;
    glm::quat Rotation;
    glm::vec3 Scale;
    
    Transform()
        : Position(glm::ZeroVector)
        , Rotation(glm::IdentityQuaternion)
        , Scale(glm::OneVector)
    {}

    Transform(const glm::vec3 position, const glm::quat& rotation = glm::IdentityQuaternion, const glm::vec3& scale = glm::OneVector)
        : Position(position)
        , Rotation(rotation)
        , Scale(scale)
    {
    }
    
    Transform(const glm::mat4& transform)
        : Position()
        , Rotation()
        , Scale()
    {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(transform, Scale, Rotation, Position, skew, perspective);
    }
    
    explicit operator glm::mat4() const
    {
        glm::mat4 transform = glm::IdentityMatrix;
        transform = glm::translate(transform, Position);
        transform *= glm::toMat4(Rotation);
        transform = glm::scale(transform, Scale);
        return transform;
    }

    glm::vec3 Forward() const { return glm::LookAt(Rotation, glm::ForwardVector); }
    glm::vec3 Up() const { return glm::LookAt(Rotation, glm::UpVector); }
    glm::vec3 Right() const { return glm::LookAt(Rotation, glm::RightVector); }
};
