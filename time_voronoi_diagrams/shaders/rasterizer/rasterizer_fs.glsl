#version 430

uniform vec3 color;

in gs_output
{
    flat vec2 fst;
    flat vec2 snd;
    flat float dist;
} f_in;

layout(location = 0) out uvec2 out_seg;
layout(location = 1) out uint out_dist_color;

void main()
{
    uvec2 seg;
    seg.x = packUnorm2x16(f_in.fst);
    seg.y = packUnorm2x16(f_in.snd);

    uint dist_color;
    dist_color = packHalf2x16(vec2(f_in.dist, color.x));

    out_seg = seg;
    out_dist_color = dist_color;
}
