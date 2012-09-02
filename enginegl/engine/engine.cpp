#include <enginegl.h>

namespace enginegl
{

using namespace  glm;

struct engine_t
    : i_engine
{

    //i_engine
public:

    void matrix_mode(GLenum matrix_type)
    {
        glMatrixMode(matrix_type);
    }

    GLenum get_matrix_mode()
    {
        GLint matrix_mode;
        glGetIntegerv(GL_MATRIX_MODE, &matrix_mode);
        return matrix_mode;
    }

    void load_identity()
    {
        glLoadIdentity();
    }

    void load_matrix(mat4 const& matrix)
    {
        glLoadMatrixf(&matrix[0][0]);
    }

    void get_matrix(mat4& matrix)
    {
        if (get_matrix_mode() == GL_MODELVIEW)
            glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0][0]);
        else
            glGetFloatv(GL_PROJECTION_MATRIX, &matrix[0][0]);
    }

    void clear_color(vec4 rgba)
    {
        glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
    }

    void clear(GLbitfield buffers_bits)
    {
        glClear(buffers_bits);
    }


    void color(vec3 rgb)
    {
        glColor3fv(&rgb[0]);
    }

    void color(vec4 rgba)
    {
        glColor4fv(&rgba[0]);
    }

    void vertex(vec2 xy)
    {
        glVertex2fv(&xy[0]);
    }

    void vertex(vec3 xyz)
    {
        glVertex3fv(&xyz[0]);
    }

    void vertex(vec4 xyzw)
    {
        glVertex4fv(&xyzw[0]);
    }

    void begin(GLenum primitive_type)
    {
        glBegin(primitive_type);
    }

    void end()
    {
        glEnd();
    }
};

void initialize_engine()
{
    if (engine)
        return;
    engine.reset(new engine_t());
}

}

enginegl::engine_ptr enginegl::engine;
