#ifndef BUFFER_TARGETS_H
#define BUFFER_TARGETS_H

#include <glebuffer_target.h>

namespace gle
{

struct buffer_target_t
    : virtual i_buffer_target_t
{
public:
    buffer_target_t(buffer_target_type_t type);

protected:
    buffer_target_t(buffer_generic_target_type_t type);

    // i_buffer_target_t
public:
    buffer_generic_target_type_t type( ) const;

    void bind_buffer( buffer_ptr buffer );
    void bind_buffer_range( buffer_ptr buffer, size_t offset, size_t length );

    void reset_binding( );

    buffer_ptr current_buffer( ) const;

protected:
    void set_current_buffer( buffer_ptr buffer );
    void reset_current_buffer( );

private:
    buffer_generic_target_type_t type_;

    buffer_ptr current_buffer_;
};

struct indexed_buffer_target_t
    : virtual i_indexed_buffer_target_t
    , buffer_target_t
{
    indexed_buffer_target_t(buffer_indexed_target_type_t type, size_t idx);

public:
    size_t idx( ) const;

    void bind_buffer( buffer_ptr buffer );
    void bind_buffer_range( buffer_ptr buffer, size_t offset, size_t length );

    void reset_binding( );

private:
    size_t idx_;
};

}

#endif // BUFFER_TARGETS_H
