#include "texture_manager.h"

#include "textures/texture.h"
#include "textures/buffer_texture.h"

namespace gle
{


GLenum gl_texture_binding(int binding)
{
    return GL_TEXTURE0 + binding;
}

struct texture_manager_t::storage_t
{
    typedef std::map<texture_binding_t, generic_texture_ptr> texture_binding_map_t;
    typedef std::map<image_binding_t, texture_ptr> image_binding_map_t;

    texture_binding_map_t tex_units;
    image_binding_map_t image_units;
};

texture_manager_t::texture_manager_t()
    : storage_(new storage_t())
{}

texture_manager_t::~texture_manager_t() {}

texture_ptr texture_manager_t::create_texture(texture_target_t target)
{
    return texture_ptr(new texture_t(new_id(), target),
                       boost::bind(&delete_texture, _1));
}

buffer_texture_ptr texture_manager_t::create_buffer_texture()
{
    return buffer_texture_ptr(new buffer_texture_t(new_id()),
                              boost::bind(&delete_texture, _1));
}

texture_binding_t texture_manager_t::bind_texture(generic_texture_ptr tex)
{
    texture_binding_t binding = free_texture_unit();
    storage_->tex_units.insert(std::make_pair(binding, tex));
    glActiveTexture(gl_texture_binding(binding));
    glBindTexture(tex->target(), tex->gl_id());

    return binding;
}

image_binding_t texture_manager_t::bind_image(texture_ptr tex, int level, image_texture_access_t access,
                                              GLenum format)
{
    image_binding_t binding = free_image_unit();
    storage_->image_units.insert(std::make_pair(binding, tex));
    glBindImageTexture(binding, tex->gl_id(), level, false, 0, access, format);

    return binding;
}

void texture_manager_t::unbind_texture(texture_binding_t binding)
{
    glActiveTexture(gl_texture_binding(binding));
    glBindTexture(storage_->tex_units.at(binding)->target(), 0);
    storage_->tex_units.erase(binding);
}

void texture_manager_t::unbind_image(image_binding_t binding)
{
    glBindImageTexture(binding, 0, 0, false, 0, ITA_read_only, GL_R8UI);
    storage_->image_units.erase(binding);
}

GLuint texture_manager_t::new_id()
{
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

void texture_manager_t::delete_texture(i_generic_texture * tex)
{
    GLuint id = tex->gl_id();
    glDeleteTextures(1, &id);
    delete tex;
}

int texture_manager_t::free_image_unit()
{
    for (int i = 0;; i++)
    {
        if (!storage_->image_units.count(i))
            return i;
    }
}

int texture_manager_t::free_texture_unit()
{
    for (int i = 0;; i++)
    {
        if (!storage_->tex_units.count(i))
            return i;
    }
}

}
