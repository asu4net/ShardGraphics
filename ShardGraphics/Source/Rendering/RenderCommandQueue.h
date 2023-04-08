﻿#pragma once
#include <memory>
#include <vector>
#include "RenderCommand.h"

namespace Shard::Graphics
{
    class RenderCommandQueue
    {
    public:
        RenderCommandQueue() = default;
        bool IsEmpty() const  { return m_CommandQueue.empty(); }
        
        template<typename T, typename ...TArgs>
        void Submit(TArgs&& ...args)
        {
            std::shared_ptr<T> command = std::make_shared<T>(std::forward<TArgs>(args)...);
            m_CommandQueue.push_back(command);
        }

        void ExecuteNext();
        
    private:
        std::vector<std::shared_ptr<RenderCommand>> m_CommandQueue; 
    };
}
