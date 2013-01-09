#version 430

in vs_output
{
    vec2 st;
} f_in;

uniform sampler2D tex_draw;

layout(location = 0) out vec4 out_color;

void main(void)
{
    out_color = textureLod(tex_draw, f_in.st, 0).xyzw;
}
