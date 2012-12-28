#ifndef GLEQUERY_H
#define GLEQUERY_H

#include <GL/glew.h>
#include <boost/shared_ptr.hpp>

namespace gle
{
    struct i_query
    {
        virtual bool is_result_ready() const = 0;

        virtual GLuint gl_id() const = 0;
        virtual GLenum gl_target() const = 0;
        virtual GLuint gl_idx() const = 0;

        virtual ~i_query() {}
    };
    typedef boost::shared_ptr<i_query> query_ptr;

    struct i_bounded_query
        : virtual i_query
    {
        virtual void begin_query() = 0;
        virtual void end_query() = 0;
    };
    typedef boost::shared_ptr<i_bounded_query> bounded_query_ptr;

    struct i_primitives_generated_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_PRIMITIVES_GENERATED;

        virtual long long primitives_generated() const = 0;
    };
    typedef boost::shared_ptr<i_primitives_generated_query> primitives_generated_query_ptr;

    struct i_transform_feedback_primitives_written_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN;

        virtual long long primitivers_written() const = 0;
    };
    typedef boost::shared_ptr<i_transform_feedback_primitives_written_query> transform_feedback_primitives_written_query_ptr;

    struct i_time_elapsed_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_TIME_ELAPSED;

        virtual long long time_elapsed_ns() const = 0;
    };
    typedef boost::shared_ptr<i_time_elapsed_query> time_elapsed_query_ptr;

    struct i_timestamp_query
        : virtual i_query
    {
        static const GLenum target = GL_TIMESTAMP;

        virtual long long timestamp() const = 0;
    };
    typedef boost::shared_ptr<i_timestamp_query> timestamp_query_ptr;

    struct i_any_samples_passed_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_ANY_SAMPLES_PASSED;

        virtual bool any_samples_passed() const = 0;
    };
    typedef boost::shared_ptr<i_any_samples_passed_query> any_samples_passed_query_ptr;

    struct i_any_samples_passed_conservative_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_ANY_SAMPLES_PASSED_CONSERVATIVE;

        virtual bool any_samples_passed_conservative() const = 0;
    };
    typedef boost::shared_ptr<i_any_samples_passed_conservative_query> any_samples_passed_conservative_query_ptr;

    struct i_samples_passed_query
        : virtual i_bounded_query
    {
        static const GLenum target = GL_SAMPLES_PASSED;

        virtual long long samples_passed() const = 0;
    };
    typedef boost::shared_ptr<i_samples_passed_query> samples_passed_query_ptr;
}

#endif // GLEQUERY_H
