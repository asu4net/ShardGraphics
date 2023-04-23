workspace "ShardGraphics"
    architecture "x86_64"
    startproject "ShardGraphics-Examples"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Engine/Dependencies"
    include "Dependencies/ShardCore/ShardCore/premake5.lua"
group ""

group "Engine"
    include "ShardGraphics/premake5.lua"
group ""

group "Game"

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
        "%{Include.ShardCore}",
        "%{Include.glm}",
        "%{Include.imgui}",
        "%{Include.imguizmo}"
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

group ""