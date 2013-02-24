#include <glevertex_format.h>

namespace gle
{

void int_vertex_format::set_format(shader_input_variable_ptr var) const
{
    glVertexAttribIFormat(var->location(), size(), type(), relative_offset());
}

void float_vertex_format::set_format(shader_input_variable_ptr var) const
{
    glVertexAttribFormat(var->location(), size(), type(), normalized(), relative_offset());
}

}
