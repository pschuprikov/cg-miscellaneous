#ifndef GLEQUERY_OBJECT_MANAGER_H
#define GLEQUERY_OBJECT_MANAGER_H

#include <glequery.h>

namespace gle
{

struct i_query_object_manager
{
    virtual primitives_generated_query_ptr create_primitives_generated_query(int idx = 0) = 0;
    virtual primitives_generated_query_ptr active_primitives_generated_query(int idx = 0) const = 0;

    virtual transform_feedback_primitives_written_query_ptr create_transform_feedback_primitives_written_query(int idx = 0) = 0;
    virtual transform_feedback_primitives_written_query_ptr active_transform_feedback_primitives_written_query(int idx = 0) const = 0;

    virtual timestamp_query_ptr create_timestamp_query() = 0;

    virtual time_elapsed_query_ptr create_time_elapsed_query() = 0;
    virtual time_elapsed_query_ptr active_time_elapsed_query() const = 0;

    virtual any_samples_passed_query_ptr create_any_samples_passed_query() = 0;
    virtual any_samples_passed_query_ptr active_any_samples_passed_query() const = 0;

    virtual any_samples_passed_conservative_query_ptr create_any_samples_passed_conservative_query() = 0;
    virtual any_samples_passed_conservative_query_ptr active_any_samples_passed_conservative_query() const = 0;

    virtual samples_passed_query_ptr create_samples_passed_query() = 0;
    virtual samples_passed_query_ptr active_samples_passed_query() const = 0;

    virtual ~i_query_object_manager() {}
};

}

#endif // GLEQUERY_OBJECT_MANAGER_H
