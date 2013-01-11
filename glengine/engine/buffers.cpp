#include "buffers.h"

#include <boost/variant/static_visitor.hpp>

namespace gle
{

    buffer_t::buffer_t(GLuint id)
        : id_(id), map_info_(), size_(0), current_usage_(BU_unknown)
    {}

    GLuint buffer_t::gl_id( ) const { return id_; }

    GLbitfield buffer_t::gl_access_flags( ) const { return map_info_.access_flags(); }

    buffer_map_info_t const& buffer_t::buffer_map_info( ) const { return map_info_; }

    size_t buffer_t::size( ) const { return size_; }

    void * buffer_t::map_pointer( ) const { return map_info_.pointer(); }
    size_t buffer_t::map_offset( ) const { return map_info_.offset(); }
    size_t buffer_t::map_length( ) const { return map_info_.length(); }

    bool buffer_t::mapped( ) const { return map_info_; }

    void buffer_t::buffer_sub_data( size_t offset, size_t size, const void * data )
    {
        glNamedBufferSubDataEXT(id_, offset, size, data);
    }

    void buffer_t::buffer_data( buffer_usage_t usage, size_t size, const void * data )
    {
        size_ = size;
        current_usage_ = usage;
        glNamedBufferDataEXT(id_, size, data, gl_buffer_usage(usage));
    }

    void buffer_t::map_buffer_range( size_t offset, size_t length, GLbitfield access )
    {
        void * ptr = glMapNamedBufferRangeEXT(id_, offset, length, access);
        map_info_ = buffer_map_info_t(ptr, access, length, offset);
    }

    void buffer_t::map_buffer( GLbitfield access )
    {
        void * ptr = glMapNamedBufferEXT(id_, access);
        map_info_ = buffer_map_info_t(ptr, access);
    }

    void buffer_t::flush_buffer_range( size_t offset, size_t length )
    {
        glFlushMappedNamedBufferRangeEXT(id_, offset, length);
    }

    void buffer_t::unmap_buffer( )
    {
        glUnmapNamedBufferEXT(id_);
    }

    buffer_usage_t buffer_t::current_usage( ) const
    {
        return current_usage_;
    }
}
