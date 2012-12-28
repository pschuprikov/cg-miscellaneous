#include "buffer_targets.h"

#include <boost/variant/static_visitor.hpp>

namespace
{

using namespace gle;

struct generic_target_type_visitor : boost::static_visitor<GLenum>
{
    GLenum operator()(buffer_target_type_t const& type) const
    {
        switch (type)
        {
            case BTT_array : return GL_ARRAY_BUFFER; case BTT_copy_read : return GL_COPY_READ_BUFFER; case BTT_copy_write : return GL_COPY_WRITE_BUFFER;
            case BTT_dispatch_indirect : return GL_DISPATCH_INDIRECT_BUFFER; case BTT_draw_indirect : return GL_DRAW_INDIRECT_BUFFER; case BTT_element_array : return GL_ELEMENT_ARRAY_BUFFER;
            case BTT_pixel_pack : return GL_PIXEL_PACK_BUFFER; case BTT_pixel_unpack : return GL_PIXEL_UNPACK_BUFFER; case BTT_texture_buffer : return GL_TEXTURE_BUFFER;
            default: return 0;
        }
    }

    GLenum operator()(buffer_indexed_target_type_t const& type) const
    {
        switch (type)
        {
            case BITT_atomic_counter : return GL_ATOMIC_COUNTER_BUFFER; case BITT_shader_storage : return GL_SHADER_STORAGE_BUFFER;
            case BITT_transform_feedback : return GL_TRANSFORM_FEEDBACK_BUFFER; case BITT_uniform : return GL_UNIFORM_BUFFER;
            default: return 0;
        }
    }
};

}

inline GLenum gle::gl_target_type(buffer_generic_target_type_t const& target_type)
{
    static generic_target_type_visitor visitor;
    return target_type.apply_visitor(visitor);
}

namespace gle
{

buffer_target_t::buffer_target_t( buffer_target_type_t type )
    : type_(type)
{}

buffer_target_t::buffer_target_t( buffer_generic_target_type_t type )
    : type_(type)
{}

buffer_generic_target_type_t buffer_target_t::type( ) const
{ return type_; }


void buffer_target_t::bind_buffer( buffer_ptr buffer )
{
    set_current_buffer(buffer);
    glBindBuffer(gl_target_type(type_), buffer->gl_id());
}


void buffer_target_t::reset_binding( )
{
    current_buffer_.reset();
    glBindBuffer(gl_target_type(type_), 0);
}

buffer_ptr buffer_target_t::current_buffer( ) const
{
    return current_buffer_;
}

void buffer_target_t::set_current_buffer( buffer_ptr buffer )
{
    current_buffer_ = buffer;
}

void buffer_target_t::reset_current_buffer( )
{
    current_buffer_.reset();
}

indexed_buffer_target_t::indexed_buffer_target_t(buffer_indexed_target_type_t type, size_t idx)
    : buffer_target_t(buffer_generic_target_type_t(type))
    , idx_(idx)
{ }


size_t indexed_buffer_target_t::idx( ) const
{
    return idx_;
}

void indexed_buffer_target_t::bind_buffer( buffer_ptr buffer )
{
    set_current_buffer(buffer);
    glBindBufferBase(gl_target_type(type()), idx_, buffer->gl_id());
}

void indexed_buffer_target_t::bind_buffer_range( buffer_ptr buffer, size_t offset, size_t length )
{
    set_current_buffer(buffer);
    glBindBufferRange(gl_target_type(type()), idx_, buffer->gl_id(), offset, length);
}

void indexed_buffer_target_t::reset_binding( )
{
    reset_current_buffer();
    glBindBufferBase(gl_target_type(type()), idx_, 0);
}

}
