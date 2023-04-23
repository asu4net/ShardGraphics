include "Dependencies.lua"

project "ShardGraphics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/Source/**.h",
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Dependencies/ShardCore/ShardCore/Source/**.h",
        "%{wks.location}/Dependencies/ThirdParty/glm/Source/**.h",
        "%{wks.location}/Dependencies/ThirdParty/glm/Source/**.cpp",
        "%{wks.location}/Dependencies/ThirdParty/glm/Source/**.hpp",
        "%{wks.location}/Dependencies/ThirdParty/imgui/Source/**.h",
        "%{wks.location}/Dependencies/ThirdParty/imguizmo/Source/**.h",
        "%{wks.location}/Dependencies/ThirdParty/imguizmo/Source/**.cpp",
        "%{prj.location}/Dependencies/ThirdParty/glad/Source/**.h",
        "%{prj.location}/Dependencies/ThirdParty/glad/Source/**.c",
        "%{prj.location}/Dependencies/ThirdParty/glfw/Source/**.h",
        "%{prj.location}/Dependencies/ThirdParty/stb/Source/**.h"
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{Include.ShardCore}",
        "%{Include.glm}",
        "%{Include.imgui}",
        "%{Include.imguizmo}",
        "%{Include.glad}",
        "%{Include.glad}",
        "%{Include.glfw}",
        "%{Include.stb}"
    }

    libdirs
    {
        "%{Library.glfw}",
        "%{Library.imgui}"
    }

    links
    {
        "ShardCore",
        "glfw3.lib",
        "opengl32.lib",
        "imgui.lib"
    }

    defines 
    { 
        "_GLFW_WIN32",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        defines "SH_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "SH_RELEASE"
        runtime "Release"
        optimize "on"