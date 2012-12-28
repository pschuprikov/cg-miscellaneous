#ifndef BUFFERS_H
#define BUFFERS_H

#include <glebuffer.h>

namespace gle
{

struct buffer_map_info_t
{
private:
    void * pointer_;
    size_t offset_;
    size_t length_;
    GLbitfield access_flags_;

public:
    void * pointer( ) const { return pointer_; }
    size_t offset( ) const { return offset_; }
    size_t length( )  const { return length_; }
    GLbitfield access_flags( ) const { return access_flags_; }

    buffer_map_info_t( )
        : pointer_(NULL), offset_(0), length_(0), access_flags_(0)
    {}

    buffer_map_info_t( void * pointer, GLbitfield access_flags, size_t length = -1, size_t offset = 0 )
        : pointer_(pointer), offset_(offset), length_(length), access_flags_(access_flags)
    {}

    operator bool() const { return pointer_ == NULL; }
};

struct buffer_t
    : i_buffer
{
    buffer_t(GLuint id);

public:
    GLuint gl_id( ) const;
    GLbitfield gl_access_flags( ) const;

    buffer_map_info_t const& buffer_map_info( ) const;

    size_t size( ) const;

    void * map_pointer( ) const;
    size_t map_offset( ) const;
    size_t map_length( ) const;

    bool mapped( ) const;

    void buffer_sub_data( size_t offset, size_t size, const void * data );
    void buffer_data( buffer_usage_t usage,  size_t size, const void * data );

    buffer_usage_t current_usage( ) const;

    void map_buffer_range( size_t offset, size_t length, GLbitfield access );
    void map_buffer( GLbitfield access );
    void flush_buffer_range( size_t offset, size_t length );

    void unmap_buffer( );

private:
    GLuint               id_;
    buffer_map_info_t    map_info_;

    size_t         size_;
    buffer_usage_t current_usage_;
};

}

#endif // BUFFERS_H
