#version 430

buffer colors
{
    coherent int cur_sample;
    int[] samples;
};

layout(location = 0) out vec4 out_color;
in vec3 col;

in gs_output
{
    vec2 color;
} f_in;

void main()
{
    atomicAdd(cur_sample, 1);
    out_color = vec4(cur_sample / float(samples[1]), f_in.color, 1);
}
