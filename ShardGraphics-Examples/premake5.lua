project "ShardGraphics-Examples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (binariesdir)
    objdir (intermediatesdir)
    
    files
    {
        "%{prj.location}/Source/**.h",
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Content/**.glsl"
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{SourceDirs.ShardCore}",
        "%{SourceDirs.ShardGraphics}",
        "%{SourceDirs.glm}",
        "%{SourceDirs.imgui}",
        "%{SourceDirs.imguizmo}",
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