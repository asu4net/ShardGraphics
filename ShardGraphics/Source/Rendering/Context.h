#pragma once
#include <functional>
#include <memory>
#include <string>

namespace Shard::Graphics
{
    std::shared_ptr<class Context> InstantiateContext(void* windowHandler);
    
    class Context
    {
        public:
#ifdef SH_DEBUG
        inline static bool EnableDebugMessages = false;
        inline static std::function<void(const std::string& message)> OnDebugMessage = [](const std::string& message){};
#endif
        Context(void* windowHandler);
        
        void Initialize();
        void SwapBuffers();
        void SetViewport(int width, int height);

    private:
        void* m_WindowHandler = nullptr;
    };
}