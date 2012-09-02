#include <enginegl.h>

#include "opengl_test_widget.h"

using namespace glm;

opengl_test_widget_t::opengl_test_widget_t(QWidget *parent) :
    QGLWidget(parent)
{
}

void opengl_test_widget_t::paintGL()
{
    enginegl::engine->clear(GL_COLOR_BUFFER_BIT);
    enginegl::engine->color(vec3(1, 0, 0));
    enginegl::engine->begin(GL_QUADS);
    enginegl::engine->vertex(vec2(0, 0));
    enginegl::engine->vertex(vec2(1, 0));
    enginegl::engine->vertex(vec2(1, 1));
    enginegl::engine->vertex(vec2(0, 1));
    enginegl::engine->end();
}

void opengl_test_widget_t::initializeGL()
{
    enginegl::initialize_engine();
    enginegl::engine->clear_color(vec4(1, 1, 1, 0));
}
