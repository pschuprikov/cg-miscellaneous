#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <gletexture_manager.h>

namespace gle
{

GLenum gl_texture_binding(int binding);

struct texture_manager_t
    : i_texture_manager
{
    texture_manager_t();
    ~texture_manager_t();

    texture_ptr create_texture(texture_target_t target);
    buffer_texture_ptr create_buffer_texture();

    texture_binding_t reserve_texture_binding();
    void release_texture_binding(texture_binding_t binding);
    image_binding_t reserve_image_binding();
    void release_image_binding(texture_binding_t binding);

    void bind_texture(texture_binding_t binding, generic_texture_ptr tex);
    void bind_image(image_binding_t binding, texture_ptr tex,
                    int level, image_texture_access_t access, GLenum internal_format);

    void unbind_texture(texture_binding_t binding);
    void unbind_image(image_binding_t binding);

private:
    struct storage_t;

private:
    static GLuint new_id();
    static void delete_texture(i_generic_texture * tex);

    int free_image_unit();
    int free_texture_unit();

private:
    boost::scoped_ptr<storage_t> storage_;
};

}

#endif // TEXTURE_MANAGER_H
