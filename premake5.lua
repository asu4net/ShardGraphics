workspace "ShardGraphics"
    architecture "x86_64"
    startproject "ShardGraphics-Examples"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "ShardGraphics/premake5.lua"

project "ShardGraphics-Examples"
    location "ShardGraphics-Examples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Content/**.glsl"
    }
    
    includedirs
    {
        "%{prj.name}/Source",
        "ShardGraphics/Source",
        "ShardGraphics/Thirdparty/ShardCore/ShardCore/Source",
        "ShardGraphics/Thirdparty/glm/Source",
        "ShardGraphics/Thirdparty/imgui/Source",
        "ShardGraphics/Thirdparty/imguizmo/Source"
    }

    links
    {
        "ShardGraphics"
    }

    postbuildcommands
	{
		("{COPY} ../%{file.relpath}/Content ../Binaries/" .. outputdir .. "/%{prj.name}/Content")
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