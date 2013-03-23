#include "texture.h"

namespace gle
{

texture_t::texture_t(GLuint id, texture_target_t target)
    : id_(id), target_(target)
    , width_(0), height_(0), depth_(0)
{}


void texture_t::set_min_filter(texture_min_filter_t filter)
{
    glTextureParameteriEXT(id_, target_, GL_TEXTURE_MIN_FILTER, filter);
}

void texture_t::set_mag_filter(texture_mag_filter_t filter)
{
    glTextureParameteriEXT(id_, target_, GL_TEXTURE_MAG_FILTER, filter);
}

void texture_t::image_2d(int level, int internal_format, int width, int height, int border,
                      GLenum format, GLenum type, const void * data)
{
    if (!is_2d_supported(target_))
        throw texture_target_mismatch_exception();

    internal_format_ = internal_format;

    width_ = width;
    height_ = height;
    depth_ = 1;

    glTextureImage2DEXT(id_, target_, level, internal_format, width, height, border, format, type, data);
}

void texture_t::get_image(int level, GLenum format, GLenum type, void * data) const
{
    glGetTextureImageEXT(id_, target_, level, format, type, data);
}

void texture_t::image_1d(int level, int internal_format, int width, int border,
                      GLenum format, GLenum type, const void * data)
{
    if (!is_1d_supported(target_))
        throw texture_target_mismatch_exception();

    internal_format_ = internal_format;

    width_ = width;
    height_ = 1;
    depth_ = 1;

    glTextureImage1DEXT(id_, target_, level, internal_format, width, border, format, type, data);
}

}
