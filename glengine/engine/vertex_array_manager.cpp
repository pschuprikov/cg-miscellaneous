#include "vertex_array_manager.h"
#include "vertex_array.h"

namespace gle
{

struct vertex_array_manager_t::storage_t
{
    typedef boost::shared_ptr<vertex_array_t> vertex_array_impl_ptr;
    typedef boost::weak_ptr<vertex_array_t> vertex_array_impl_weakptr;
    std::map<GLuint, vertex_array_impl_weakptr> vaos;
};

vertex_array_ptr vertex_array_manager_t::create_vertex_array()
{
    GLuint id;
    glGenVertexArrays(1, &id);
    storage_t::vertex_array_impl_ptr vao_ptr(new vertex_array_t(id),
        boost::bind(&vertex_array_manager_t::delete_vertex_array, this, _1));
    storage_->vaos.insert(std::make_pair(id, storage_t::vertex_array_impl_weakptr(vao_ptr)));
    return vao_ptr;
}

vertex_array_manager_t::vertex_array_manager_t()
    : storage_(new storage_t())
{}

vertex_array_manager_t::~vertex_array_manager_t()
{}

void vertex_array_manager_t::set_current(vertex_array_ptr vao)
{
    if (vao)
    {
        glBindVertexArray(vao->gl_id());
        storage_->vaos.at(vao->gl_id()).lock()->apply();
    }
    current_ = vao;
}

void vertex_array_manager_t::reset_current()
{
    glBindVertexArray(0);
    current_.reset();
}

void vertex_array_manager_t::delete_vertex_array(i_vertex_array * array)
{
    GLuint id = array->gl_id();
    glDeleteVertexArrays(1, &id);
    delete array;
    storage_->vaos.erase(id);
}

void vertex_array_manager_t::draw_arrays(drawing_mode_t mode, int first, int count)
{
    glDrawArrays(mode, first, count);
}

void vertex_array_manager_t::draw_elements(drawing_mode_t mode, int count, GLenum type, const void * indicies)
{
    glDrawElements(mode, count, type, indicies);
}

}
