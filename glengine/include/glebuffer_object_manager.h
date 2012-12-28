#ifndef GLEBUFFER_OBJECT_MANAGER_H
#define GLEBUFFER_OBJECT_MANAGER_H

#include <glebuffer.h>
#include <glebuffer_target.h>

namespace gle
{

struct i_buffer_object_manager
{
    virtual buffer_ptr create_buffer( ) = 0;
    virtual i_indexed_buffer_target_t * buffer_target( buffer_indexed_target_type_t target, size_t idx ) = 0;
    virtual i_buffer_target_t * buffer_target( buffer_target_type_t target ) = 0;

    virtual ~i_buffer_object_manager() {}
};

}

#endif // GLEBUFFER_OBJECT_MANAGER_H
