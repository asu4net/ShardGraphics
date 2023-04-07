#pragma once
#include "Defaults.h"
#include "Utils.h"

struct Transform
{
    glm::vec3 Position = glm::ZeroVector;
    glm::quat Rotation = glm::IdentityQuaternion;
    glm::vec3 Scale = glm::OneVector;

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