Include = {}
Library = {}

-- Global

Include["ShardCore"] = "%{wks.location}/Dependencies/ShardCore/ShardCore/Source"
Include["glm"]       = "%{wks.location}/Dependencies/ThirdParty/glm/Source"
Include["imgui"]     = "%{wks.location}/Dependencies/ThirdParty/imgui/Source"
Include["imguizmo"]  = "%{wks.location}/Dependencies/ThirdParty/imguizmo/Source"

Library["imgui"]     = "%{wks.location}/Dependencies/ThirdParty/imgui/Binaries"

-- ShardGraphics

Include["glad"] = "%{wks.location}/ShardGraphics/Dependencies/ThirdParty/glad/Source"
Include["glfw"] = "%{wks.location}/ShardGraphics/Dependencies/ThirdParty/glfw/Source"
Include["stb"]  = "%{wks.location}/ShardGraphics/Dependencies/ThirdParty/stb/Source"

Library["glfw"] = "%{wks.location}/ShardGraphics/Dependencies/ThirdParty/glfw/Binaries"