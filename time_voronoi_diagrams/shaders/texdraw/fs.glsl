#version 430

in vs_output
{
    vec2 st;
} f_in;

uniform layout(rgba32ui) readonly uimage2D img_vd;

layout(location = 0) out vec4 out_color;

void main(void)
{
    uvec2 packed_color_dist = imageLoad(img_vd, ivec2(f_in.st * imageSize(img_vd))).zw;

    vec4 color_dist;
    color_dist.xy = unpackHalf2x16(packed_color_dist.x);
    color_dist.zw = unpackHalf2x16(packed_color_dist.y);

    out_color = vec4(color_dist.rgb * 0.5, 1);
}
