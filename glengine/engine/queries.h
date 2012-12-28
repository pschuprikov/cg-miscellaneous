#ifndef QUERIES_H
#define QUERIES_H

#include "../include/glequery.h"
#include "query_object_manager.h"

namespace gle
{
    struct query_t
        : virtual i_query
    {
    protected:
        query_t(GLuint id, GLenum target, GLuint idx);

    // i_query
    public:
        bool is_result_ready() const;

        GLuint     gl_id() const { return id_; }
        GLuint    gl_idx() const { return idx_; }
        GLenum gl_target() const { return target_; }

    protected:
        GLint64 get_result() const;

    private:
        GLuint id_;
        GLenum target_;        GLuint idx_;
    };

    struct bounded_query_t
        : query_t
        , virtual i_bounded_query
    {
    protected:
        bounded_query_t(GLuint id, GLenum target, GLuint idx)
            : query_t(id, target, idx)
        {}

    // i_bounded_query
    public:
        void begin_query();
        void end_query();
    };

    struct primitives_generated_query_t
        : bounded_query_t
        , i_primitives_generated_query
    {
        using bounded_query_t::begin_query;
        using bounded_query_t::end_query;

        primitives_generated_query_t(GLuint id, GLuint idx)
            : bounded_query_t(id, target, idx)
        {}

        long long primitives_generated() const { return get_result(); }
    };

    struct transform_feedback_primitives_written_query_t
        : bounded_query_t
        , i_transform_feedback_primitives_written_query
    {
        using bounded_query_t::begin_query;
        using bounded_query_t::end_query;

        transform_feedback_primitives_written_query_t(GLuint id, GLuint idx)
            : bounded_query_t(id, target, idx)
        {}

        long long primitivers_written() const { return get_result(); }
    };

    struct time_elapsed_query_t
        : bounded_query_t
        , i_time_elapsed_query
    {
        time_elapsed_query_t(GLuint id)
            : bounded_query_t(id, target, 0)
        {}

        long long time_elapsed_ns() const { return get_result(); }
    };

    struct timestamp_query_t
        : query_t
        , i_timestamp_query
    {
        timestamp_query_t(GLuint id);

        long long timestamp() const { return get_result(); }
    };

    struct any_samples_passed_query_t
        : bounded_query_t
        , i_any_samples_passed_query
    {
        any_samples_passed_query_t(GLuint id)
            : bounded_query_t(id, target, 0)
        {}

        bool any_samples_passed() const { return get_result(); }
    };

    struct any_samples_passed_conservative_query_t
        : bounded_query_t
        , i_any_samples_passed_conservative_query
    {
        any_samples_passed_conservative_query_t(GLuint id)
            : bounded_query_t(id, target, 0)
        {}

        bool any_samples_passed_conservative() const { return get_result(); }
    };

    struct samples_passed_query_t
        : bounded_query_t
        , i_samples_passed_query
    {
        samples_passed_query_t(GLuint id)
            : bounded_query_t(id, target, 0)
        {}

        long long samples_passed() const { return get_result(); }
    };
}

#endif // QUERIES_H
