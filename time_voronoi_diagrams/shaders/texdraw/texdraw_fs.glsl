#version 430

in vs_output
{
    vec2 st;
} f_in;

uniform layout(r16ui) readonly uimage2D img_vd;
uniform layout(rgba32ui) uimage1D img_vd_data;

layout(location = 0) out vec4 out_color;

void main(void)
{
    uint id = imageLoad(img_vd, ivec2(f_in.st * imageSize(img_vd))).r;

    if (id != 0xffffu)
    {
        uvec2 packed_dist_color = imageLoad(img_vd_data, int(id)).zw;
        vec4 dist_color;
        dist_color.xy = unpackHalf2x16(packed_dist_color.x);
        dist_color.zw = unpackHalf2x16(packed_dist_color.y);
        out_color = vec4(dist_color.yzw, 1);
    }
    else
        out_color = vec4(0);
}
