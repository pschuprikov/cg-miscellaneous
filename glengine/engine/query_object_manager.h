#ifndef QUERY_OBJECT_MANAGER_H
#define QUERY_OBJECT_MANAGER_H

#include <boost/scoped_ptr.hpp>

#include <glequery_object_manager.h>

#include "query_ptrs_storage_fwd.hpp"

namespace gle
{

struct query_object_manager_t
    : i_query_object_manager
{
    query_object_manager_t();

    primitives_generated_query_ptr create_primitives_generated_query(int idx = 0);
    primitives_generated_query_ptr active_primitives_generated_query(int idx = 0) const;

    transform_feedback_primitives_written_query_ptr create_transform_feedback_primitives_written_query(int idx = 0);
    transform_feedback_primitives_written_query_ptr active_transform_feedback_primitives_written_query(int idx = 0) const;

    timestamp_query_ptr create_timestamp_query();

    time_elapsed_query_ptr create_time_elapsed_query();
    time_elapsed_query_ptr active_time_elapsed_query() const;

    any_samples_passed_query_ptr create_any_samples_passed_query();
    any_samples_passed_query_ptr active_any_samples_passed_query() const;

    any_samples_passed_conservative_query_ptr create_any_samples_passed_conservative_query();
    any_samples_passed_conservative_query_ptr active_any_samples_passed_conservative_query() const;

    samples_passed_query_ptr create_samples_passed_query();
    samples_passed_query_ptr active_samples_passed_query() const;

    ~query_object_manager_t();

private:
    inline GLuint current_id(GLenum target, GLuint idx = 0) const;
    inline GLuint new_id() const;

    template<class Query>
    inline void delete_query(Query * query);

    template<class QueryPtr, class QueryImpl>
    inline QueryPtr create_query();

    template<class QueryPtr, class QueryImpl>
    inline QueryPtr create_indexed_query(int idx);

private:
    boost::scoped_ptr<query_ptrs_storage_t> query_ptrs_;
};

}

#endif // QUERY_OBJECT_MANAGER_H
