#ifndef GLETEXTURE_MANAGER_H
#define GLETEXTURE_MANAGER_H

#include <gletexture.h>

namespace gle
{

typedef int texture_binding_t;
typedef int image_binding_t;

enum image_texture_access_t { ITA_read_only = GL_READ_ONLY,
                              ITA_write_only = GL_WRITE_ONLY,
                              ITA_read_write = GL_READ_WRITE
                            };

GLenum gl_texture_binding(int binding);

struct i_texture_manager
{
    virtual texture_ptr create_texture(texture_target_t target) = 0;
    virtual buffer_texture_ptr create_buffer_texture() = 0;

    virtual texture_binding_t reserve_texture_binding() = 0;
    virtual void release_texture_binding(texture_binding_t binding) = 0;
    virtual image_binding_t reserve_image_binding() = 0;
    virtual void release_image_binding(texture_binding_t binding) = 0;

    virtual void bind_texture(texture_binding_t binding, generic_texture_ptr tex) = 0;
    virtual void bind_image(image_binding_t binding, texture_ptr tex,
                            int level, image_texture_access_t access, GLenum internal_format) = 0;

    virtual void unbind_texture(texture_binding_t binding) = 0;
    virtual void unbind_image(image_binding_t binding) = 0;

    virtual ~i_texture_manager() {}
};

}
#endif // GLETEXTURE_MANAGER_H
