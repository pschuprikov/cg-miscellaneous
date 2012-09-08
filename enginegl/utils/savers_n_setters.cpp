#include <savers_n_setters.h>

namespace eg
{
    using namespace enginegl;
    using namespace glm;

    matrix_mode_setter_t::matrix_mode_setter_t(GLenum matrix_mode)
    {
        old_mode_ = engine->get_matrix_mode();
        engine->matrix_mode(matrix_mode);
    }

    matrix_mode_setter_t::~matrix_mode_setter_t()
    {
        engine->matrix_mode(old_mode_);
    }

    matrix_setter_t::matrix_setter_t(engine_ptr engine, GLenum matrix_mode, mat4 const& matrix)
        : engine_(engine)
        , matrix_mode_(matrix_mode)
    {
        matrix_mode_setter_t setter(matrix_mode);
        engine->get_matrix(old_);
        engine->load_matrix(matrix);
    }

    matrix_setter_t::~matrix_setter_t()
    {
        matrix_mode_setter_t setter(matrix_mode_);
        engine->load_matrix(old_);
    }
}
