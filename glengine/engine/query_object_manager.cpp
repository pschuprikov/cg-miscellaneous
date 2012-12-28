#include <map>

#include <boost/bind.hpp>
#include <boost/fusion/container/map.hpp>

#include "query_object_manager.h"
#include "query_ptrs_storage.hpp"
#include "queries.h"

namespace gle
{

using namespace boost;


query_object_manager_t::query_object_manager_t()
    : query_ptrs_(new query_ptrs_storage_t())
{}

query_object_manager_t::~query_object_manager_t() {}

GLuint query_object_manager_t::new_id() const
{
    GLuint id;
    glGenQueries(1, &id);
    return id;
}

GLuint query_object_manager_t::current_id(GLenum target, GLuint idx) const
{
    GLint res;
    glGetQueryIndexediv(target, idx, GL_CURRENT_QUERY, &res);
    return res;
}


template<class Query>
void query_object_manager_t::delete_query(Query * query)
{
    GLuint id = query->gl_id();
    glDeleteQueries(1, &id);
    query_ptrs_->delete_query(query);
}


template<class QueryPtr, class QueryImpl>
QueryPtr query_object_manager_t::create_query()
{
    typedef typename QueryPtr::element_type query_type;
    return query_ptrs_->register_query(QueryPtr(new QueryImpl(new_id()),
        boost::bind(&query_object_manager_t::delete_query<query_type>, this, _1)));
}

template<class QueryPtr, class QueryImpl>
QueryPtr query_object_manager_t::create_indexed_query(int idx)
{
    typedef typename QueryPtr::element_type query_type;
    return query_ptrs_->register_query(QueryPtr(new QueryImpl(new_id(), idx),
        boost::bind(&query_object_manager_t::delete_query<query_type>, this, _1)));
}


primitives_generated_query_ptr query_object_manager_t::create_primitives_generated_query(int idx)
{
    return create_indexed_query<primitives_generated_query_ptr, primitives_generated_query_t>(idx);
}

primitives_generated_query_ptr query_object_manager_t::active_primitives_generated_query(int idx) const
{
    return query_ptrs_->find_query<primitives_generated_query_ptr>(current_id(i_primitives_generated_query::target, idx));
}

transform_feedback_primitives_written_query_ptr
query_object_manager_t::create_transform_feedback_primitives_written_query(int idx)
{
    return create_indexed_query<transform_feedback_primitives_written_query_ptr, transform_feedback_primitives_written_query_t>(idx);
}

transform_feedback_primitives_written_query_ptr
query_object_manager_t::active_transform_feedback_primitives_written_query(int idx) const
{
    return query_ptrs_->find_query<transform_feedback_primitives_written_query_ptr>(current_id(i_transform_feedback_primitives_written_query::target, idx));
}

timestamp_query_ptr query_object_manager_t::create_timestamp_query()
{
    return create_query<timestamp_query_ptr, timestamp_query_t>();
}

time_elapsed_query_ptr query_object_manager_t::create_time_elapsed_query()
{
    return create_query<time_elapsed_query_ptr, time_elapsed_query_t>();
}

time_elapsed_query_ptr query_object_manager_t::active_time_elapsed_query() const
{
    return query_ptrs_->find_query<time_elapsed_query_ptr>(current_id(i_time_elapsed_query::target));
}

any_samples_passed_query_ptr query_object_manager_t::create_any_samples_passed_query()
{
    return create_query<any_samples_passed_query_ptr, any_samples_passed_query_t>();
}

any_samples_passed_query_ptr query_object_manager_t::active_any_samples_passed_query() const
{
    return query_ptrs_->find_query<any_samples_passed_query_ptr>(current_id(i_any_samples_passed_query::target));
}

any_samples_passed_conservative_query_ptr query_object_manager_t::create_any_samples_passed_conservative_query()
{
    return create_query<any_samples_passed_conservative_query_ptr, any_samples_passed_conservative_query_t>();
}

any_samples_passed_conservative_query_ptr query_object_manager_t::active_any_samples_passed_conservative_query() const
{
    return query_ptrs_->find_query<any_samples_passed_conservative_query_ptr>(current_id(i_any_samples_passed_conservative_query::target));
}

samples_passed_query_ptr query_object_manager_t::create_samples_passed_query()
{
    return create_query<samples_passed_query_ptr, samples_passed_query_t>();
}

samples_passed_query_ptr query_object_manager_t::active_samples_passed_query() const
{
    return query_ptrs_->find_query<samples_passed_query_ptr>(current_id(i_samples_passed_query::target));
}

}
