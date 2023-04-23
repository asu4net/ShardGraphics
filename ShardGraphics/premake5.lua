include "Libraries.lua"

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
        "%{SourceDirs.ShardCore}/**.h",
        "%{SourceDirs.glm}/**.h",
        "%{SourceDirs.glm}/**.cpp",
        "%{SourceDirs.glm}/**.hpp",
        "%{SourceDirs.imgui}/**.h",
        "%{SourceDirs.imguizmo}/**.h",
        "%{SourceDirs.imguizmo}/**.cpp",
        "%{SourceDirs.glad}/**.h",
        "%{SourceDirs.glad}/**.c",
        "%{SourceDirs.glfw}/**.h",
        "%{SourceDirs.stb}/**.h"
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{SourceDirs.ShardCore}",
        "%{SourceDirs.glm}",
        "%{SourceDirs.imgui}",
        "%{SourceDirs.imguizmo}",
        "%{SourceDirs.glad}",
        "%{SourceDirs.glfw}",
        "%{SourceDirs.stb}"
    }

    libdirs
    {
        "%{BinaryDirs.glfw}",
        "%{BinaryDirs.imgui}"
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