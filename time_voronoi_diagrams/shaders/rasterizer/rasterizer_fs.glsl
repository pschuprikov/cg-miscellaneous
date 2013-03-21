#version 430

layout(location = 0) out uint out_idx;

flat in uint g_out_idx;

void main()
{
    out_idx = g_out_idx;
}
