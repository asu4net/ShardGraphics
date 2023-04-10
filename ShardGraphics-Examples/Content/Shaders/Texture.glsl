#type vertex
#version 410 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;

uniform mat4 u_MvpMatrix;

out vec2 v_UV;

void main()
{
    gl_Position = u_MvpMatrix * vec4(a_Position, 1.0);
    v_UV = a_UV;
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;
in vec2 v_UV;

uniform vec4 u_Color;
uniform sampler2D u_TextureSlot;

void main()
{
    //color = vec4(v_UV, 0.0, 1.0);
    color = texture(u_TextureSlot, v_UV) * u_Color;
}