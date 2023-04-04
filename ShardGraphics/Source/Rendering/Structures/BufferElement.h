#pragma once
#include <string>
#include "ShaderDataType.h"

namespace Shard::Graphics
{
    struct BufferElement
    {
        ShaderDataType type;
        std::string name;
        bool normalized;
        uint32_t size;
        uint32_t offset;
        
        BufferElement()
            : type(ShaderDataType::None)
            , normalized(false)
            , size(0)
            , offset(0)
        {}
        
        BufferElement(const ShaderDataType type, const std::string& name, const bool normalized = false)
            : type(type)
            , name(name)
            , normalized(normalized)
            , size(ShaderDataTypeToSize(type))
            , offset(0)
        {}

        uint32_t GetComponentCount() const
        {
            switch (type)
            {
            case ShaderDataType::None:   return 0;
            case ShaderDataType::Float:  return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3:   return 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4;
            case ShaderDataType::Int:    return 1;
            case ShaderDataType::Int2:   return 2;
            case ShaderDataType::Int3:   return 3;
            case ShaderDataType::Int4:   return 4;
            case ShaderDataType::Bool:   return 1;
            default:                     return 0;
            }
        }
    };
}