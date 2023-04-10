#include "Time.h"
#include <glfw/glfw3.h>

namespace Shard::Graphics
{
    double Time::GetTime()
    {
        return glfwGetTime();
    }
}