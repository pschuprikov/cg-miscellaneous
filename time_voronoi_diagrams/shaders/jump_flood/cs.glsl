#version 430

layout(local_size_x = 8, local_size_y = 8) in;

uniform float outer_velocity;
uniform float max_distance;

uniform int jump_step;

uniform layout(rgba32ui) uimage2D img_vd;

void unpack_params(in uvec4 texel, out vec4 segment, out float prefix_dist)
{
    prefix_dist = unpackHalf2x16(texel.w)[1];

    segment.xy = unpackUnorm2x16(texel.x);
    segment.zw = unpackUnorm2x16(texel.y);
}

float cross_2d(in vec2 v1, in vec2 v2)
{
    return fma(v1.x, v2.y, -v1.y * v2.x);
}

vec2 calc_optimal(in vec4 seg, in float prefix_dist, in vec2 pos)
{
   float cur_dist = max_distance * 2;
   float out_dist;

   vec2 dir = normalize(seg.zw - seg.xy);

   vec2 r1 = pos - seg.xy;
   vec2 r2 = pos - seg.zw;

   float sin_alpha = outer_velocity;
   float cos_alpha = sqrt(1 - sin_alpha * sin_alpha);

   mat2 rot = mat2(sin_alpha, -cos_alpha,
                   cos_alpha,  sin_alpha);

   vec2 dir1 = rot * dir;
   vec2 dir2 = transpose(rot) * dir;

   float c1 = cross_2d(dir, r1);

   vec2 proj;

   if (dot(dir, r1) >= 0 && (cross_2d(dir1, r2) <= 0 || cross_2d(dir2, r2) >= 0))
   {
      rot = mat2(cos_alpha, -sin_alpha,
                 sin_alpha,  cos_alpha);

      dir1 = rot * dir;
      dir2 = transpose(rot) * dir;

      proj = dot(dir1, r1) * dir1;
      if (cross_2d(dir, proj) * c1 <= 0 && length(r1 - proj) / outer_velocity < cur_dist)
      {
         cur_dist = length(r1 - proj) / outer_velocity;
         out_dist = length(r1 - proj) - length(proj) * sin_alpha / cos_alpha;
      }

      proj = dot(dir2, r1) * dir2;
      if (cross_2d(dir, proj) * c1 <= 0 && length(r1 - proj) / outer_velocity < cur_dist)
      {
        cur_dist = length(r1 - proj) / outer_velocity;
        out_dist = length(r1 - proj) - length(proj) * sin_alpha / cos_alpha;
      }
   }

   if (distance(pos, seg.xy) / outer_velocity < cur_dist)
   {
      cur_dist = distance(pos, seg.xy) / outer_velocity;
      out_dist = distance(pos, seg.xy);
   }
   if (distance(pos, seg.zw) / outer_velocity + distance(seg.xy, seg.zw) < cur_dist)
   {
      cur_dist = distance(pos, seg.zw) / outer_velocity + distance(seg.xy, seg.zw);
      out_dist = distance(pos, seg.zw);
   }
   return vec2(cur_dist + prefix_dist, out_dist / outer_velocity);
}

void main(void)
{
    float min_dist = max_distance * 2;

    const ivec2 max_idx = imageSize(img_vd) - 1;
    const ivec2 my_coord = ivec2(min(gl_GlobalInvocationID.xy, max_idx));
    const vec2 pos = my_coord / vec2(imageSize(img_vd));

    uvec4 best;

    for (int i = -1; i <= 1; i++)
    {
       for (int j = -1; j <= 1; j++)
       {
          uvec4 cur = imageLoad(img_vd, min(max_idx, my_coord + ivec2(i, j) * jump_step));

          if (cur == uvec4(0, 0, 0, 0))
              continue;

          vec4 seg;
          float prefix_dist;
          unpack_params(cur, seg, prefix_dist);

          float cur_dist = calc_optimal(seg, prefix_dist, pos).x;

          if (cur_dist < min_dist && cur_dist < max_distance)
          {
             min_dist = cur_dist;
             best = cur;
          }
       }
    }

    if (min_dist != max_distance * 2) {
        imageStore(img_vd, my_coord, best);
    }
}
