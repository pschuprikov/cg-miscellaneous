#ifndef TEXTURE_H
#define TEXTURE_H

#include <gletexture.h>

namespace gle
{

struct texture_t
    : i_texture
{
    texture_t(GLuint id, texture_target_t target);

    // i_generic_texture
public:
    GLuint gl_id() const { return id_; }
    texture_target_t target() const { return target_; }

    int internal_format() const { return internal_format_; }

    // i_texture:
public:
    void set_min_filter(texture_min_filter_t filter);
    void set_mag_filter(texture_mag_filter_t filter);


    int width() const { return width_; }
    int height() const { return height_; }
    int depth() const { return depth_; }


    void image_2d(int level, int internal_format, int width, int height, int border,
                          GLenum format, GLenum type, const void * data);

    void image_1d(int level, int internal_format, int width, int border,
                          GLenum format, GLenum type, const void * data);

    void get_image(int level, GLenum format, GLenum type, void *data) const;

private:
    GLuint id_;

    texture_target_t target_;

    int width_;
    int height_;
    int depth_;

    int internal_format_;
};

}

#endif // TEXTURE_H
