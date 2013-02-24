#ifndef GLEBLENDING_H
#define GLEBLENDING_H

namespace gle
{

enum blend_equation_t
{
    BE_add = GL_FUNC_ADD,
    BE_subtract = GL_FUNC_SUBTRACT,
    BE_revers_subtract = GL_FUNC_REVERSE_SUBTRACT,
    BE_min = GL_MIN,
    BE_max = GL_MAX
};

enum blend_function_t
{
    BF_zero = GL_ZERO,
    BF_one  = GL_ONE ,
    BF_src_color = GL_SRC_COLOR,
    BF_one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
    BF_dst_color = GL_DST_COLOR,
    BF_one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
    BF_src_alpha = GL_SRC_ALPHA,
    BF_one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
    BF_dst_alpha = GL_DST_ALPHA,
    BF_one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA
};

struct blending_t
{
    blending_t()
        : eq_(BE_add), src_(BF_src_alpha), dst_(BF_one_minus_src_alpha)
    {}

    blending_t(blend_equation_t eq, blend_function_t src, blend_function_t dst)
        : eq_(eq), src_(src), dst_(dst)
    {}

    blend_equation_t equation() const { return eq_; }
    blend_function_t src() const { return src_; }
    blend_function_t dst() const { return dst_; }

private:
    blend_equation_t eq_;
    blend_function_t src_;
    blend_function_t dst_;
};

}

#endif // GLEBLENDING_H
