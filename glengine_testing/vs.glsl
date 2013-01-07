#version 430

layout(location = 0) in vec4 pos;

uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * pos;
}
