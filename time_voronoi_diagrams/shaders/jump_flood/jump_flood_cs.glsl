#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform vec3 outer_params; // sin_alpha (outer_velocity)
                            // 1 / outer_velocity
                            // cos_alpha

const float sin_alpha = outer_params.x;
const float cos_alpha = outer_params.z;
const float ov_rec = outer_params.y * outer_params.y;

const mat2 rot0 = mat2(sin_alpha, -cos_alpha,
                       cos_alpha, sin_alpha);

const mat2 rot1 = mat2(cos_alpha, -sin_alpha,
                       sin_alpha,  cos_alpha);

uniform float max_distance;

uniform mat2 velocity_rotation;

uniform int jump_step;

uniform layout(rgba32ui) uimage2D img_vd_in;
uniform layout(rgba32ui) writeonly uimage2D img_vd_out;

void unpack_params(inout uvec4 texel, out vec4 segment, out float prefix_dist)
{
    prefix_dist = unpackHalf2x16(texel.w)[1];
    segment.xy = unpackUnorm2x16(texel.x);
    segment.zw = unpackUnorm2x16(texel.y);
}

float cross_2d(inout vec2 v1, inout vec2 v2)
{
    return fma(v1.x, v2.y, -v1.y * v2.x);
}

const ivec2 max_idx = imageSize(img_vd_in) - 1;
const ivec2 my_coord = ivec2(min(gl_GlobalInvocationID.xy, max_idx));
const vec2 pos = my_coord / vec2(imageSize(img_vd_in));

float calc_optimal(inout vec4 seg, inout float prefix_dist)
{
   float cur_dist_sqr = max_distance * max_distance * 4;

   vec2 dir = normalize(seg.zw - seg.xy);

   vec2 r1 = pos - seg.xy;
   vec2 r2 = pos - seg.zw;

   vec2 dir1 = rot0 * dir;
   vec2 dir2 = transpose(rot0) * dir;

   float c1 = cross_2d(dir, r1);

   vec2 proj;

   float maybe_dist_sqr = 0;

   if (dot(dir, r1) >= 0 && (cross_2d(dir1, r2) <= 0 || cross_2d(dir2, r2) >= 0))
   {
      dir1 = rot1 * dir;
      dir2 = transpose(rot1) * dir;

      proj = dot(dir1, r1) * dir1;
      maybe_dist_sqr = dot(r1 - proj, r1 - proj) * ov_rec;
      if (c1 >= 0)
         cur_dist_sqr = min(maybe_dist_sqr, cur_dist_sqr);

      proj = dot(dir2, r1) * dir2;
      maybe_dist_sqr = dot(r1 - proj, r1 - proj) * ov_rec;
      if (c1 <= 0 && maybe_dist_sqr < cur_dist_sqr)
          cur_dist_sqr = min(maybe_dist_sqr, cur_dist_sqr);
   }

   maybe_dist_sqr = dot(pos - seg.xy, pos - seg.xy);
   if (maybe_dist_sqr < cur_dist_sqr)
      cur_dist_sqr = maybe_dist_sqr;

   maybe_dist_sqr = distance(pos, seg.zw) * sqrt(ov_rec) + distance(seg.xy, seg.zw);
   maybe_dist_sqr *= maybe_dist_sqr;
   if (maybe_dist_sqr < cur_dist_sqr)
      cur_dist_sqr = maybe_dist_sqr;

   return sqrt(cur_dist_sqr) + prefix_dist;
}

void check_best(inout float min_dist, inout uvec4 best, in const uvec4 cur, in const float cur_dist)
{
    if (cur_dist < min_dist && cur_dist < max_distance && cur != uvec4(0))
    {
       min_dist = cur_dist;
       best = cur;
    }
}

void main(void)
{
    float min_dist = max_distance * 2;

    vec4 seg;
    float prefix_dist;

    uvec4 best;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            uvec4 cur = imageLoad(img_vd_in, my_coord + ivec2(i, j) * jump_step);
            unpack_params(cur, seg, prefix_dist);
            check_best(min_dist, best, cur, calc_optimal(seg, prefix_dist));
        }
    }

    if (min_dist != max_distance * 2) {
        imageStore(img_vd_in, my_coord, best);
    }
}
