#pragma once
#include "Defaults.h"
#include "Utils.h"

struct Transform
{
    glm::vec3 Position = glm::ZeroVector;
    glm::vec3 Rotation = glm::ZeroVector;
    glm::vec3 Scale = glm::OneVector;

    explicit operator glm::mat4() const
    {
        glm::mat4 transform = glm::IdentityMatrix;
        transform = glm::translate(transform, Position);
        transform *= glm::toMat4(glm::quat(Rotation));
        transform = glm::scale(transform, Scale);
        return transform;
    }

    glm::vec3 Forward() const { return glm::LookAt(glm::quat(Rotation), glm::ForwardVector); }
    glm::vec3 Up() const { return glm::LookAt(glm::quat(Rotation), glm::UpVector); }
    glm::vec3 Right() const { return glm::LookAt(glm::quat(Rotation), glm::RightVector); }
};