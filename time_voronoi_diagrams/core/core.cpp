#include "core.h"
#include "input_manager.h"
#include "render_manager.h"

namespace tvd
{

namespace
{

void idle_func()
{
    core_t::instance()->treat();
}

}

core_t * core_t::instance()
{
    static core_t core;
    return &core;
}

void core_t::run(logic_ptr start_logic, int x, int y, int width, int height, std::string const& title)
{
    glutInitWindowPosition(x, y);
    glutInitWindowSize(width, height);
    glutCreateWindow(title.c_str());

    glutIdleFunc(idle_func);

    logics_.reset(new logic_processor_t(start_logic));
    input_manager_t::instance();
    render_manager_t::instance();
    // enter GLUT event processing cycle
    glutMainLoop();
}

void core_t::treat()
{
    input_manager_t::instance()->clear();
    render_manager_t::instance()->clear();
    logics_->treat(this);
    usleep(1000);
}

i_input_manager * core_t::input() { return input_manager_t::instance(); }
i_render_manager * core_t::rendering() { return render_manager_t::instance(); }


}
