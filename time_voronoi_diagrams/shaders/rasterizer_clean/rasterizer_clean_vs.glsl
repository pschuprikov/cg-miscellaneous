#version 430

layout(location = 0) in vec2 in_pos;

void main(void)
{
    gl_Position = vec4(2 * in_pos - 1, 0, 1);
}
