#version 430

layout(location = 0) out uvec2 out_seg;
layout(location = 1) out uint out_dist_color;

void main()
{
    out_seg = uvec2(0);
    out_dist_color = packHalf2x16(vec2(-1.f, -1.f));
}
