#ifndef VERTEX_ARRAY_MANAGER_H
#define VERTEX_ARRAY_MANAGER_H

#include <glevertex_array_manager.h>

namespace gle
{

struct vertex_array_manager_t
    : i_vertex_array_manager
{
    vertex_array_manager_t();
    ~vertex_array_manager_t();

    // i_vertex_array_manager
public:
    vertex_array_ptr create_vertex_array();
    vertex_array_ptr current() const { return current_; }
    void set_current(vertex_array_ptr vao);
    void reset_current();

private:
    void delete_vertex_array(i_vertex_array * array);

private:
    struct storage_t;

private:
    vertex_array_ptr current_;
    boost::scoped_ptr<storage_t> storage_;
};

}

#endif // VERTEX_ARRAY_MANAGER_H
