#ifndef SAVERS_N_SETTERS_H
#define SAVERS_N_SETTERS_H

#include "enginegl.h"

namespace eg
{
    using namespace enginegl;
    using namespace glm;

    struct matrix_mode_setter_t
    {
        matrix_mode_setter_t(GLenum matrix_mode)
        {
            old_mode_ = engine->get_matrix_mode();
            engine->matrix_mode(matrix_mode);
        }

        ~matrix_mode_setter_t()
        {
            engine->matrix_mode(old_mode_);
        }

    private:
        GLenum old_mode_;
    };

    struct matrix_setter_t
    {
        matrix_setter_t(engine_ptr engine, GLenum matrix_mode, mat4 const& matrix)
            : engine_(engine)
            , matrix_mode_(matrix_mode)
        {
            matrix_mode_setter_t setter(matrix_mode);
            engine->get_matrix(old_);
            engine->load_matrix(matrix);
        }

        ~matrix_setter_t()
        {
            matrix_mode_setter_t setter(matrix_mode_);
            engine->load_matrix(old_);
        }

    private:
        engine_ptr engine_;
        GLenum matrix_mode_;
        mat4 old_;
    };
}

#endif // SAVERS_N_SETTERS_H
