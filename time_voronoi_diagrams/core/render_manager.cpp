#include "render_manager.h"

namespace tvd
{

namespace
{

void display_func()
{
    render_manager_t::instance()->display();
}

void reshape_func(int width, int height)
{
    render_manager_t::instance()->reshape(width, height);
}

}

render_manager_t * render_manager_t::instance()
{
    static render_manager_t rm(gle::default_engine());
    bool initialized = false;
    if (!initialized)
    {
        glutDisplayFunc(display_func);
        glutReshapeFunc(reshape_func);
    }
    return &rm;
}

void render_manager_t::reshape(int width, int height)
{
    engine_->set_viewport(gle::viewport_t(0, 0, width, height));
}

void render_manager_t::display()
{
    gle::default_engine()->clear(gle::BPB_color | gle::BPB_depth);
    for (size_t i = 0; i < renderables_.size(); i++)
    {
        renderables_[i]->render();
    }
    glutSwapBuffers();
}

void render_manager_t::invalidate()
{
    glutPostRedisplay();
}

}
