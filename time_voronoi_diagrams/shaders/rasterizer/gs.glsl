#version 430

layout (lines) in;

in vs_output
{
    vec2 pos;
    float dist;
} g_in[2];

layout (line_strip, max_vertices = 2) out;
out gs_output
{
    flat vec2 fst;
    flat vec2 snd;
    flat float dist;
} g_out;

void main(void)
{
    g_out.fst = g_in[0].pos;
    g_out.snd = g_in[1].pos;
    g_out.dist = g_in[0].dist;
    gl_Position = vec4(2 * g_in[0].pos - 1, 0 ,1);
    EmitVertex();
    g_out.fst = g_in[0].pos;
    g_out.snd = g_in[1].pos;
    g_out.dist = g_in[0].dist;
    gl_Position = vec4(2 * g_in[1].pos - 1, 0 ,1);
    EmitVertex();
}
