#version 430

layout(local_size_x = 128, local_size_y = 2) in;

uniform vec3 outer_params; // sin_alpha (outer_velocity)
                            // 1 / outer_velocity
                            // cos_alpha

const float sin_alpha = outer_params.x;
const float cos_alpha = outer_params.z;
const float ov_rec = outer_params.y;

const mat2 rot0 = mat2(sin_alpha, -cos_alpha,
                       cos_alpha, sin_alpha);

const mat2 rot1 = mat2(cos_alpha, -sin_alpha,
                       sin_alpha,  cos_alpha);

uniform float max_distance;

uniform mat2 velocity_rotation;

uniform int jump_step;

uniform layout(r16ui) uimage2D img_vd;
uniform layout(rgba32ui) readonly uimage1D img_lines_data;

void unpack_seg(in uvec4 texel, out vec4 segment, out float max_dist)
{
    segment.xy = unpackUnorm2x16(texel.x);
    segment.zw = unpackUnorm2x16(texel.y);
    max_dist = unpackHalf2x16(texel.z)[0];
}

float cross_2d(inout vec2 v1, inout vec2 v2)
{
    return fma(v1.x, v2.y, -v1.y * v2.x);
}

float calc_optimal(inout vec4 seg, inout float prefix_dist, in vec2 pos)
{
   float cur_dist = max_distance * 2;

   vec2 dir = normalize(seg.zw - seg.xy);

   vec2 r1 = pos - seg.xy;
   vec2 r2 = pos - seg.zw;

   vec2 dir1 = rot0 * dir;
   vec2 dir2 = transpose(rot0) * dir;

   float c1 = cross_2d(dir, r1);

   vec2 proj;

   if (dot(dir, r1) >= 0 && (cross_2d(dir1, r2) <= 0 || cross_2d(dir2, r2) >= 0))
   {
      dir1 = rot1 * dir;
      dir2 = transpose(rot1) * dir;

      proj = dot(dir1, r1) * dir1;
      if (cross_2d(dir, proj) * c1 <= 0 && length(r1 - proj) * ov_rec < cur_dist)
      {
         cur_dist = length(r1 - proj) * ov_rec;;
      }

      proj = dot(dir2, r1) * dir2;
      if (cross_2d(dir, proj) * c1 <= 0 && length(r1 - proj) * ov_rec < cur_dist)
      {
        cur_dist = length(r1 - proj) * ov_rec;
      }
   }

   if (distance(pos, seg.xy) * ov_rec < cur_dist)
   {
      cur_dist = distance(pos, seg.xy) * ov_rec;
   }

   if (distance(pos, seg.zw) * ov_rec + distance(seg.xy, seg.zw) < cur_dist)
   {
      cur_dist = distance(pos, seg.zw) * ov_rec + distance(seg.xy, seg.zw);
   }
   return cur_dist + prefix_dist;
}

const ivec2 max_idx = imageSize(img_vd) - 1;
const ivec2 my_coord = ivec2(min(gl_GlobalInvocationID.xy, max_idx));
const vec2 pos = my_coord / vec2(imageSize(img_vd));

void check_best(inout float min_dist, inout uint best,
                in const uint cur, in const float cur_dist)
{
    if (cur_dist < min_dist && cur_dist < max_distance)
    {
       min_dist = cur_dist;
       best = cur;
    }
}

void main(void)
{
    float min_dist = max_distance * 2;

    uint best;

    for (int i = -1; i <= 1; i++)
    {
       for (int j = -1; j <= 1; j++)
       {
          ivec2 coord = my_coord + ivec2(i, j) * jump_step;

          uint cur = imageLoad(img_vd, clamp(coord, ivec2(0), max_idx)).r;

          if (cur != 0xffff)
          {
              vec4 seg;
              float prefix_dist;
              uvec4 texel = imageLoad(img_lines_data, int(cur));
              unpack_seg(texel, seg, prefix_dist);
              check_best(min_dist, best, cur, calc_optimal(seg, prefix_dist, pos));
          }
       }
    }

    if (min_dist < max_distance * 2) {
        imageStore(img_vd, my_coord, uvec4(best));
    }
}
