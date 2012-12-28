#ifndef GLEBUFFER_TARGET_H
#define GLEBUFFER_TARGET_H

#include <glecommon.h>
#include <glebuffer.h>

#include <boost/variant.hpp>

namespace gle
{

enum buffer_target_type_t { BTT_array, BTT_copy_read, BTT_copy_write, BTT_dispatch_indirect, BTT_draw_indirect, BTT_element_array, BTT_pixel_pack,
                            BTT_pixel_unpack, BTT_texture_buffer };
enum buffer_indexed_target_type_t { BITT_atomic_counter, BITT_shader_storage, BITT_transform_feedback, BITT_uniform };

typedef boost::variant<buffer_target_type_t, buffer_indexed_target_type_t> buffer_generic_target_type_t;

inline GLenum gl_target_type(buffer_generic_target_type_t const& target_type);

struct i_buffer_target_t
{
    virtual buffer_generic_target_type_t type( ) const = 0;

    virtual void bind_buffer( buffer_ptr buffer ) = 0;

    virtual void reset_binding( ) = 0;

    virtual buffer_ptr current_buffer( ) const = 0;

    virtual ~i_buffer_target_t( ) { }
};

struct i_indexed_buffer_target_t
    : virtual i_buffer_target_t
{
    virtual size_t idx() const = 0;

    virtual void bind_buffer_range( buffer_ptr buffer, size_t offset, size_t length ) = 0;
};

}

#endif // GLEBUFFER_TARGET_H
