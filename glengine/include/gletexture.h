#ifndef GLETEXTURE_H
#define GLETEXTURE_H

#include <glecommon.h>
#include <glebuffer.h>

namespace gle
{

enum texture_target_t { TT_rectangle = GL_TEXTURE_RECTANGLE,
                        TT_1d = GL_TEXTURE_1D,
                        TT_2d = GL_TEXTURE_2D,
                        TT_buffer = GL_TEXTURE_BUFFER
                      };

inline bool is_1d_supported(texture_target_t tgt)
{
    switch(tgt)
    {
    case TT_1d : return true;
    default : return false;
    }
}

inline bool is_2d_supported(texture_target_t tgt)
{
    switch (tgt)
    {
    case TT_2d: case TT_rectangle: return true;
    default : return false;
    }
}

struct texture_target_mismatch_exception
    : std::exception
{
    texture_target_mismatch_exception()
    {}

    const char * what() const throw()
    {
        return "texture target doesn't match first bound";
    }
};

struct i_generic_texture
{
    virtual GLuint gl_id() const = 0;
    virtual texture_target_t target() const = 0;

    virtual int internal_format() const = 0;

    virtual ~i_generic_texture() {}
};
typedef boost::shared_ptr<i_generic_texture> generic_texture_ptr;

enum texture_min_filter_t {
    TMINF_nearest = GL_NEAREST,
    TMINF_linear = GL_LINEAR,
    TMINF_nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
    TMINF_nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
    TMINF_linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
    TMINF_linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR
};

enum texture_mag_filter_t {
    TMAGF_nearest = GL_NEAREST,
    TMING_linear = GL_LINEAR
};

struct i_texture
    : i_generic_texture
{
    virtual void set_min_filter(texture_min_filter_t filter) = 0;
    virtual void set_mag_filter(texture_mag_filter_t filter) = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual int depth() const = 0;

    virtual void image_2d(int level, int internal_format, int width, int height, int border,
                          GLenum format, GLenum type, const void * data) = 0;

    virtual void image_1d(int level, int internal_format, int width, int border,
                          GLenum format, GLenum type, const void * data) = 0;
};
typedef boost::shared_ptr<i_texture> texture_ptr;

struct i_buffer_texture
    : i_generic_texture
{
    virtual void set_buffer(GLenum internal_format, buffer_ptr buf) = 0;
    virtual void reset_buffer() = 0;
    virtual buffer_ptr buffer() const = 0;
};
typedef boost::shared_ptr<i_buffer_texture> buffer_texture_ptr;

}

#endif // GLETEXTURE_H
