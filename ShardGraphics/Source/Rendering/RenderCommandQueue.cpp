#include "RenderCommandQueue.h"
#include "RenderCommand.h"

namespace Shard::Graphics
{
    void RenderCommandQueue::Submit(const std::shared_ptr<RenderCommand>& renderCommand)
    {
        m_CommandQueue.push_back(renderCommand);
    }
    
    void RenderCommandQueue::ExecuteNext()
    {
        if (m_CommandQueue.empty()) return;
        const auto& command = m_CommandQueue[0];
        //printf("%s\n", command->GetName());
        command->Execute();
        m_CommandQueue.erase(m_CommandQueue.begin());
    }
}
