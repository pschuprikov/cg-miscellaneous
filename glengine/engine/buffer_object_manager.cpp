#include "buffer_object_manager.h"
#include "buffer_targets.h"
#include "buffers.h"

#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

namespace gle
{

i_indexed_buffer_target_t * buffer_object_manager_t::buffer_target( buffer_indexed_target_type_t target, size_t idx )
{
    indexed_target_idx_t id(target, idx);
    if (!indexed_targets_[id])
        indexed_targets_[id] = indexed_buffer_target_ptr(new indexed_buffer_target_t(target, idx));
    return indexed_targets_[id].get();
}

i_buffer_target_t * buffer_object_manager_t::buffer_target( buffer_target_type_t target )
{
    if (!targets_[target])
        targets_[target] = buffer_target_ptr(new buffer_target_t(target));
    return targets_[target].get();
}


buffer_ptr buffer_object_manager_t::create_buffer( )
{
    GLuint id;
    glGenBuffers(1, &id);
    return buffer_ptr(new buffer_t(id), boost::bind(&buffer_object_manager_t::delete_buffer, _1));
}

void buffer_object_manager_t::delete_buffer( i_buffer * bt )
{
    GLuint id = bt->gl_id();
    glDeleteBuffers(1, &id);
    delete bt;
}

}
