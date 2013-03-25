#version 430

layout (lines) in;

in vs_output
{
    vec2 pos;
    float dist;
    int idx;
} g_in[2];

flat out uint g_out_idx;

layout (line_strip, max_vertices = 2) out;

uniform layout (rgba32ui) writeonly uimage1D img_lines_data;
uniform int offset;

uniform vec3 color;

void main(void)
{
    uvec4 data;
    data.x = packUnorm2x16(g_in[0].pos);
    data.y = packUnorm2x16(g_in[1].pos);
    data.z = packHalf2x16(vec2(g_in[0].dist, color.r));
    data.w = packHalf2x16(color.gb);

    imageStore(img_lines_data, g_in[0].idx + offset, data);

    gl_Position = vec4(2 * g_in[0].pos - 1, 0 ,1);
    g_out_idx = g_in[0].idx + offset;
    EmitVertex();
    gl_Position = vec4(2 * g_in[1].pos - 1, 0 ,1);
    g_out_idx = g_in[0].idx + offset;
    EmitVertex();
}
