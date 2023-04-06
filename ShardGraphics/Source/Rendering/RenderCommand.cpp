#include "RenderCommand.h"
#include "RendererAPI.h"

namespace Shard::Graphics
{
    RenderCommand::RenderCommand()
    {
        m_RendererAPI.reset(RendererAPI::Create());
    }
}