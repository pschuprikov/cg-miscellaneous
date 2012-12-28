#ifndef GLEBUFFER_H
#define GLEBUFFER_H

#include <glecommon.h>

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

namespace gle
{

enum buffer_usage_t { BU_static_draw,  BU_static_read,  BU_static_copy,
                      BU_stream_draw,  BU_stream_read,  BU_stream_copy,
                      BU_dynamic_draw, BU_dynamic_read, BU_dynamic_copy, BU_unknown };

inline GLenum gl_buffer_usage(buffer_usage_t usage)
{
    switch(usage)
    {
    case BU_static_draw : return GL_STATIC_DRAW;   case BU_static_copy : return GL_STATIC_COPY;   case BU_static_read : return GL_STATIC_READ;
    case BU_stream_draw : return GL_STREAM_DRAW;   case BU_stream_copy : return GL_STREAM_COPY;   case BU_stream_read : return GL_STREAM_READ;
    case BU_dynamic_draw : return GL_DYNAMIC_DRAW; case BU_dynamic_copy : return GL_DYNAMIC_COPY; case BU_dynamic_read : return GL_DYNAMIC_READ;
    case BU_unknown : default: return 0;
    }
}

struct i_buffer
{
    virtual GLuint gl_id( ) const = 0;
    virtual GLbitfield gl_access_flags( ) const = 0;

    virtual size_t size( ) const = 0;

    virtual void * map_pointer( ) const = 0;
    virtual size_t  map_offset( ) const = 0;
    virtual size_t  map_length( ) const = 0;
    virtual bool        mapped( ) const = 0;

    virtual void buffer_sub_data( size_t offset, size_t size, const void * data ) = 0;
    virtual void     buffer_data( buffer_usage_t usage, size_t size, const void * data ) = 0;

    virtual buffer_usage_t current_usage( ) const = 0;

    virtual void map_buffer_range(size_t offset, size_t length, GLbitfield access) = 0;
    virtual void map_buffer(GLbitfield access) = 0;
    virtual void flush_buffer_range(size_t offset, size_t length) = 0;

    virtual void unmap_buffer() = 0;

    virtual ~i_buffer() {}
};
typedef boost::shared_ptr<i_buffer> buffer_ptr;

}

#endif // GLEBUFFER_H
