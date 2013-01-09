#version 430

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec2 in_st;

out vs_output
{
    vec2 st;
} v_out;

void main(void)
{
    v_out.st = in_st;
    gl_Position = vec4(in_pos, 0, 1);
}
