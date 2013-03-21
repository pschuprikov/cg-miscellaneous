#version 430

in vs_output
{
    vec2 st;
} f_in;

uniform layout(r32ui) readonly uimage2D img_vd;

layout(location = 0) out vec4 out_color;

void main(void)
{
    uint packed_dist_color = imageLoad(img_vd, ivec2(f_in.st * imageSize(img_vd))).r;

    vec2 dist_color;
    dist_color = unpackHalf2x16(packed_dist_color);

    if (dist_color.y >= -0.5)
        out_color = vec4(dist_color.y, 1 - dist_color.y, 0, 0);
    else
        out_color = vec4(0);
}
