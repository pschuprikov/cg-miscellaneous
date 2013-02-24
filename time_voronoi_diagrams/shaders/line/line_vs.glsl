#version 430

layout(location = 0) in vec2 in_pos;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(in_pos, 0, 1);
}
