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

uniform layout(rgba32ui) uimage2D img_vd;

uniform samplerBuffer tex_line;

uniform vec3 color;

void unpack_params(inout uvec4 texel, out vec4 segment, out float prefix_dist)
{
    prefix_dist = unpackHalf2x16(texel.w)[1];
    segment.xy = unpackUnorm2x16(texel.x);
    segment.zw = unpackUnorm2x16(texel.y);
}

uvec4 pack_params(in const vec2 fst, in const vec2 snd, in const float prefix_dist)
{
    return uvec4(packUnorm2x16(fst), packUnorm2x16(snd),
                 packHalf2x16(color.xy), packHalf2x16(vec2(color.z, prefix_dist)));
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

void check_best(inout float min_dist, inout uvec4 best, in const uvec4 cur, in const float cur_dist)
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

    uvec4 best = uvec4(0);

    float min_dist = max_distance * 2;

    uvec4 me = imageLoad(img_vd, my_coord);
    if ((me.x | me.y | me.z | me.w) != 0)
    {
        unpack_params(me, seg, prefix_dist);
        check_best(min_dist, best, me, calc_optimal(seg, prefix_dist));
    }

    vec3 prev;
    vec3 cur = texelFetch(tex_line, 0).rgb;
    for (int i = 1; i < textureSize(tex_line); i++)
    {
        prev = cur;
        cur = texelFetch(tex_line, i).rgb;
        check_best(min_dist, best, pack_params(prev.xy, cur.xy, prev.z),
                   calc_optimal(vec4(prev.xy, cur.xy), prev.z));
    }

    imageStore(img_vd, my_coord, best);
}
