#version 430

layout(location = 0) in vec2 in_pos;
layout(location = 1) in float in_dist;

out vs_output
{
    vec2 pos;
    float dist;
    int idx;
} v_out;

void main(void)
{
    v_out.pos = in_pos;
    v_out.idx = gl_VertexID;
    v_out.dist = in_dist;
}
