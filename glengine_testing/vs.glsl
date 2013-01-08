#version 430

layout(location = 0) in vec3 in_pos;

out vs_output
{
    vec3 pos;
} v_out;

void main(void)
{
    v_out.pos = in_pos;
}
