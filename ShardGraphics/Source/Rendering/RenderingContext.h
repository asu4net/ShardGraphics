#pragma once
#include <functional>
#include <memory>
#include <string>

namespace Shard::Graphics
{
    std::shared_ptr<class RenderingContext> InstantiateContext(void* windowHandler);
    
    class RenderingContext
    {
        public:
#ifdef SH_DEBUG
        inline static bool EnableDebugMessages = false;
        inline static std::function<void(const std::string& message)> OnDebugMessage = [](const std::string& message)
        {
            printf("%s \n", message.c_str());
        };
#endif
        RenderingContext(void* windowHandler);
        
        void Initialize();
        void SwapBuffers();

    private:
        void* m_WindowHandler = nullptr;
    };
}