#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform vec3 outer_params; // sin_alpha (outer_velocity)
                           // 1 / outer_velocity
                           // cos_alpha

const float ov_rec = outer_params.y * outer_params.y;

const vec2 dir1 = vec2(outer_params.x, -outer_params.z);
const vec2 dir2 = vec2(outer_params.z, -outer_params.x);

uniform float max_distance;

uniform int jump_step;

uniform layout(r16ui) uimage2D img_vd;
uniform layout(rgba32ui) uimage1D img_lines_data;

uniform uint num_segments;

uniform vec3 color;


void unpack_seg(in uvec4 texel, out vec4 segment, out float max_dist)
{
    segment.xy = unpackUnorm2x16(texel.x);
    segment.zw = unpackUnorm2x16(texel.y);
    max_dist = unpackHalf2x16(texel.z)[0];
}

float cross_2d(const in vec2 v1, const in vec2 v2)
{
    return fma(v1.x, v2.y, -v1.y * v2.x);
}

const ivec2 max_idx = imageSize(img_vd) - 1;
const ivec2 my_coord = ivec2(min(gl_GlobalInvocationID.xy, max_idx));
const vec2 pos = my_coord / vec2(imageSize(img_vd));

float calc_optimal(in const vec4 seg, in const float prefix_dist)
{
   float cur_dist_sqr = max_distance * max_distance * 4;

   vec2 dir = normalize(seg.zw - seg.xy);

   vec2 npos = pos - seg.xy;
   npos = vec2(dot(npos, vec2(dir.x, dir.y)), dot(npos, vec2(-dir.y, dir.x)));

   float len = distance(seg.zw, seg.xy);
   vec2 r2 = npos - vec2(len, 0);

   float maybe_dist_sqr;

   if (npos.x >= 0 && (cross_2d(dir1, r2) <= 0 || cross_2d(vec2(dir1.x, -dir1.y), r2) >= 0))
   {
      vec2 proj;
      proj = dot(dir2, npos) * dir2;
      maybe_dist_sqr = dot(npos - proj, npos - proj) * ov_rec;
      if (npos.y * proj.x >= 0)
         cur_dist_sqr = min(maybe_dist_sqr, cur_dist_sqr);

      proj = dot(vec2(dir2.x, -dir2.y), npos) * vec2(dir2.x, -dir2.y);
      maybe_dist_sqr = dot(npos - proj, npos - proj) * ov_rec;
      if (npos.y * proj.x <= 0)
          cur_dist_sqr = min(maybe_dist_sqr, cur_dist_sqr);
   }

   maybe_dist_sqr = dot(npos, npos) * ov_rec;
   if (maybe_dist_sqr < cur_dist_sqr)
      cur_dist_sqr = maybe_dist_sqr;

   maybe_dist_sqr = length(r2) * outer_params.y + len;
   maybe_dist_sqr *= maybe_dist_sqr;
   if (maybe_dist_sqr < cur_dist_sqr)
      cur_dist_sqr = maybe_dist_sqr;

   return sqrt(cur_dist_sqr) + prefix_dist;
}

void check_best(inout float min_dist, inout uint best, in const uint cur, in const float cur_dist)
{
    if (cur_dist < min_dist && cur_dist < max_distance)
    {
       min_dist = cur_dist;
       best = cur;
    }
}

void main(void)
{
    vec4 seg;
    float prefix_dist;

    uint best = 0xffff;

    float min_dist = max_distance * 2;

    for (uint i = 0; i < num_segments; i++)
    {
        uvec4 texel = imageLoad(img_lines_data, int(i));
        unpack_seg(texel, seg, prefix_dist);
        check_best(min_dist, best, i, calc_optimal(seg, prefix_dist));
    }

    imageStore(img_vd, my_coord, uvec4(best));
}
