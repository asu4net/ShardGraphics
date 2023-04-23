workspace "ShardGraphics"
    architecture "x86_64"
    startproject "ShardGraphics-Examples"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
binariesdir = "Binaries/" .. outputdir .. "/%{prj.name}"
intermediatesdir = "Intermediate/" .. outputdir .. "/%{prj.name}"

group "Engine/Libraries"
    include "Libraries/ShardCore/ShardCore/premake5.lua"
group ""

group "Engine"
    include "ShardGraphics/premake5.lua"
group ""

group "Games"
    include "ShardGraphics-Examples/premake5.lua"
group ""