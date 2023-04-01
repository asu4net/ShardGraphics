include "ThirdParty/ShardCore/ShardCore/premake5.lua"

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
        "%{prj.location}/ThirdParty/ShardCore/Source/**.h",
        "%{prj.location}/ThirdParty/glm/Source/**.h",
        "%{prj.location}/ThirdParty/glm/Source/**.cpp",
        "%{prj.location}/ThirdParty/glm/Source/**.hpp",
        "%{prj.location}/ThirdParty/glad/Source/**.h",
        "%{prj.location}/ThirdParty/glad/Source/**.c",
        "%{prj.location}/ThirdParty/glfw/Source/**.h",
        "%{prj.location}/ThirdParty/imgui/Source/**.h",
        "%{prj.location}/ThirdParty/imguizmo/Source/**.h",
        "%{prj.location}/ThirdParty/imguizmo/Source/**.cpp"
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{prj.location}/ThirdParty/ShardCore/Source",
        "%{prj.location}/ThirdParty/glm/Source",
        "%{prj.location}/ThirdParty/glad/Source",
        "%{prj.location}/ThirdParty/glad/Source",
        "%{prj.location}/ThirdParty/glfw/Source",
        "%{prj.location}/ThirdParty/imgui/Source",
        "%{prj.location}/ThirdParty/imguizmo/Source"
    }

    libdirs
    {
        "%{prj.location}/ThirdParty/glfw/Binaries",
        "%{prj.location}/ThirdParty/imgui/Binaries"
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