workspace "ShardGraphics"
    architecture "x86_64"
    startproject "ShardGraphics-Examples"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ShardGraphics"
    location "ShardGraphics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/ThirdParty/glm/Source/**.h",
        "%{prj.name}/ThirdParty/glm/Source/**.cpp",
        "%{prj.name}/ThirdParty/glm/Source/**.hpp",
        "%{prj.name}/ThirdParty/glad/Source/**.h",
        "%{prj.name}/ThirdParty/glad/Source/**.c",
        "%{prj.name}/ThirdParty/glfw/Source/**.h",
        "%{prj.name}/ThirdParty/imgui/Source/**.h",
        "%{prj.name}/ThirdParty/imguizmo/Source/**.h",
        "%{prj.name}/ThirdParty/imguizmo/Source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/Source",
        "%{prj.name}/ThirdParty/glm/Source",
        "%{prj.name}/ThirdParty/glad/Source",
        "%{prj.name}/ThirdParty/glad/Source",
        "%{prj.name}/ThirdParty/glfw/Source",
        "%{prj.name}/ThirdParty/imgui/Source",
        "%{prj.name}/ThirdParty/imguizmo/Source"
    }

    libdirs
    {
        "%{prj.name}/ThirdParty/glfw/Binaries",
        "%{prj.name}/ThirdParty/imgui/Binaries"
    }

    links
    {
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
        "%{prj.name}/Source/**.cpp"
    }
    
    includedirs
    {
        "%{prj.name}/Source",
        "ShardGraphics/Source",
        "ShardGraphics/Thirdparty/glm/Source",
        "ShardGraphics/Thirdparty/imgui/Source",
        "ShardGraphics/Thirdparty/imguizmo/Source"
    }

    links
    {
        "ShardGraphics"
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