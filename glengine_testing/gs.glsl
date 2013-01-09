#version 430

layout (triangles) in;

uniform mat4 mvp;

in vs_output
{
    vec3 pos;
} g_in[3];

layout (triangle_strip, max_vertices = 3) out;
out gs_output
{
    vec2 color;
} g_out;

uniform sampler1D tex_colors;

void main(void)
{
    g_out.color = texelFetch(tex_colors, 0, 0).xy;
    gl_Position = mvp * vec4(g_in[0].pos, 1);
    EmitVertex();
    g_out.color = texelFetch(tex_colors, 1, 0).xy;
    gl_Position = mvp * vec4(g_in[1].pos, 1);
    EmitVertex();
    g_out.color = texelFetch(tex_colors, 2, 0).xy;
    gl_Position = mvp * vec4(g_in[2].pos, 1);
    EmitVertex();
}
