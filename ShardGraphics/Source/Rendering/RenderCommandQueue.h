#pragma once
#include <memory>
#include <vector>

namespace Shard::Graphics
{
    class RenderCommand;
    
    class RenderCommandQueue
    {
    public:
        RenderCommandQueue() = default;
        bool IsEmpty() const  { return m_CommandQueue.empty(); }
        void Submit(const std::shared_ptr<RenderCommand>& renderCommand);
        void ExecuteNext();
        
    private:
        std::vector<std::shared_ptr<RenderCommand>> m_CommandQueue; 
    };
}
