#version 430

layout(location = 0) in vec2 in_pos;

uniform mat4 mvp;

out vs_output
{
    vec2 st;
} v_out;

void main(void)
{
    v_out.st = in_pos;

    gl_Position = mvp * vec4(in_pos, 0, 1);
}
