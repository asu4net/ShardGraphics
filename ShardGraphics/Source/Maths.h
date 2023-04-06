#pragma once
#include <glm/glm.hpp>
#include "glm/gtx/quaternion.hpp"

namespace glm
{

    /////////////////////////
    /// COLORS
    ////////////////////////
    
    constexpr vec4 BlackColor = { 0, 0, 0, 1 };                                                    
    constexpr vec4 BlueColor = { 0, 0, 1, 1 };                                                     
    constexpr vec4 LightBlueColor = { .3f, .3f, 1, 1 };                                            
    constexpr vec4 ClearColor = { 0, 0, 0, 0 };                                                    
    constexpr vec4 CyanColor = { 0, 1, 1, 1 };                                                     
    constexpr vec4 GrayColor = { .5f, .5f, .5f, 1 };                                               
    constexpr vec4 GreenColor = { 0, 1, 0, 1 };                                                    
    constexpr vec4 LightGreenColor = { .3f, 1, .3f, 1 };                                           
    constexpr vec4 GreyColor{.2f, .2f, .2f, 1};
    constexpr vec4 DarkGreyColor = { .13f, .13f, .13f, 1 };                                           
    constexpr vec4 MagentaColor = { 1, 0, 1, 1 };                                                  
    constexpr vec4 RedColor = { 1, 0, 0, 1 };                                                      
    constexpr vec4 LightRedColor = { 1, .3f, .3f, 1 };                                             
    constexpr vec4 WhiteColor = { 1, 1, 1, 1 };                                                    
    constexpr vec4 YellowColor = { 1, .92f, .016f, 1 };

    /////////////////////////
    /// VECTORS
    ////////////////////////

    constexpr vec3 ZeroVector = { 0, 0, 0 };    
    constexpr vec3 OneVector = { 1, 1, 1 };     
    constexpr vec3 RightVector = { 1, 0, 0 };   
    constexpr vec3 LeftVector = { -1, 0, 0 };   
    constexpr vec3 UpVector = { 0, 1, 0 };      
    constexpr vec3 DownVector = { 0, -1, 0 };   
    constexpr vec3 BackVector = { 0, 0, -1 };   
    constexpr vec3 ForwardVector = { 0, 0, 1 };

    /////////////////////////
    /// QUATERNIONS
    ////////////////////////

    constexpr quat IdentityQuaternion = {1, 0, 0, 0};

    /////////////////////////
    /// MATRICES
    ////////////////////////

    constexpr mat4 IdentityMatrix = mat4(1);
}

namespace Shard
{
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
    };
}