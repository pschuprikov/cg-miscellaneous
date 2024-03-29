#include "queries.h"

namespace gle
{

query_t::query_t(GLuint id, GLenum target, GLuint idx)
    : id_(id), target_(target), idx_(idx)
{}

bool query_t::is_result_ready() const
{
    if (!is_created() || is_active())
        return false;
    GLuint ready;
    glGetQueryObjectuiv(id_, GL_QUERY_RESULT_AVAILABLE, &ready);
    return ready;
}

GLint64 query_t::get_result() const
{
    GLint64 res;
    glGetQueryObjecti64v(id_, GL_QUERY_RESULT, &res);
    return res;
}

void bounded_query_t::begin_query()
{
    is_created_ = true;
    is_active_ = true;
    glBeginQueryIndexed(gl_target(), gl_idx(), gl_id());
}

void bounded_query_t::end_query()
{
    is_active_ = false;
    glEndQueryIndexed(gl_target(), gl_idx());
}


timestamp_query_t::timestamp_query_t(GLuint id)
    : query_t(id, GL_TIMESTAMP, 0)
    , is_created_(false)
{
    glQueryCounter(id, GL_TIMESTAMP);
}

}
