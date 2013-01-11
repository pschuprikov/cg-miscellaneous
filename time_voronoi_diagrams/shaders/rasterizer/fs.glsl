#version 430

uniform vec3 color;

in gs_output
{
    flat vec2 fst;
    flat vec2 snd;
    flat float dist;
} f_in;

layout(location = 0) out uvec4 out_color;

void main()
{
    uvec2 fst_snd;
    fst_snd.x = packUnorm2x16(f_in.fst);
    fst_snd.y = packUnorm2x16(f_in.snd);

    uvec2 color_dist;
    color_dist.x = packHalf2x16(color.xy);
    color_dist.y = packHalf2x16(vec2(color.z, f_in.dist));

    out_color = uvec4(fst_snd, color_dist);
}
