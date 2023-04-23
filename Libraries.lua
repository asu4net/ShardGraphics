SourceDirs = {}
BinaryDirs = {}

-- Global

SourceDirs["ShardCore"    ] = "%{wks.location}/Libraries/ShardCore/ShardCore/Source"
SourceDirs["glm"          ] = "%{wks.location}/Libraries/ThirdParty/glm/Source"
SourceDirs["imgui"        ] = "%{wks.location}/Libraries/ThirdParty/imgui/Source"
SourceDirs["imguizmo"     ] = "%{wks.location}/Libraries/ThirdParty/imguizmo/Source"

BinaryDirs["imgui"        ] = "%{wks.location}/Libraries/ThirdParty/imgui/Binaries"

-- ShardGraphics

SourceDirs["ShardGraphics"] = "%{wks.location}/ShardGraphics/Source"
SourceDirs["glad"         ] = "%{wks.location}/ShardGraphics/Libraries/ThirdParty/glad/Source"
SourceDirs["glfw"         ] = "%{wks.location}/ShardGraphics/Libraries/ThirdParty/glfw/Source"
SourceDirs["stb"          ] = "%{wks.location}/ShardGraphics/Libraries/ThirdParty/stb/Source"

BinaryDirs["glfw"         ] = "%{wks.location}/ShardGraphics/Libraries/ThirdParty/glfw/Binaries"