#version 430

layout (local_size_x = 16, local_size_y = 16) in;

uniform uvec4 clear_color;
uniform layout (rgba32ui) uimage2D img_clear;

const ivec2 max_idx = imageSize(img_clear) - 1;
const ivec2 my_coord = ivec2(min(gl_GlobalInvocationID.xy, max_idx));


void main()
{
    imageStore(img_clear, my_coord, clear_color);
}
