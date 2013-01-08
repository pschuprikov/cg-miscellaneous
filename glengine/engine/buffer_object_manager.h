#ifndef BUFFER_OBJECT_MANAGER_H
#define BUFFER_OBJECT_MANAGER_H

#include <glebuffer_object_manager.h>
#include <glebuffer_target.h>

#include <boost/shared_ptr.hpp>
#include <map>

namespace gle
{

struct buffer_object_manager_t
    : i_buffer_object_manager
{
    buffer_ptr create_buffer( );
    i_indexed_buffer_target_t * buffer_target( buffer_indexed_target_type_t target, size_t idx );
    i_buffer_target_t * buffer_target( buffer_target_type_t target );

private:
    static void delete_buffer( i_buffer * const bt );

private:
    typedef boost::shared_ptr<i_buffer_target_t> buffer_target_ptr;
    typedef boost::shared_ptr<i_indexed_buffer_target_t> indexed_buffer_target_ptr;

private:
    typedef std::map<buffer_target_type_t, buffer_target_ptr> target_map_t;
    typedef std::pair<buffer_indexed_target_type_t, size_t> indexed_target_idx_t;

    typedef std::map<indexed_target_idx_t, indexed_buffer_target_ptr> indexed_target_map_t;

private:
    target_map_t targets_;
    indexed_target_map_t indexed_targets_;
};

}

#endif // BUFFER_OBJECT_MANAGER_H
