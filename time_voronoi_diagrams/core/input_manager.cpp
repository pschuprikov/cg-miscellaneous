#include "input_manager.h"
#include "input_infos.h"

namespace tvd
{

namespace
{

void keyboard_func(unsigned char key, int x, int y)
{
    input_manager_t::instance()->keyboard_event(key, x, y);
}

void mouse_func(int button, int state, int x, int y)
{
    input_manager_t::instance()->mouse_event(button, state, x, y);
}

void passive_motion_func(int x, int y)
{
    input_manager_t::instance()->mouse_move(x, y);
}

}

input_manager_t * input_manager_t::instance()
{
    static input_manager_t im;
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        glutKeyboardFunc(keyboard_func);
        glutMouseFunc(mouse_func);
        glutPassiveMotionFunc(passive_motion_func);
        glutMotionFunc(passive_motion_func);
    }
    return &im;
}

void input_manager_t::keyboard_event(unsigned char key, int x, int y)
{
    keyborad_input_info_t info(key, x, y);
    for (size_t i = 0; i < input_listeners_.size(); i++)
    {
        input_listeners_[i]->key_pressed(&info);
    }
}

void input_manager_t::mouse_event(int button, int state, int x, int y)
{
    mouse_input_info_t info(button, x, y);
    for (size_t i = 0; i < input_listeners_.size(); i++)
    {
        switch(state)
        {
        case GLUT_DOWN : input_listeners_[i]->mouse_down(&info);
        case GLUT_UP : input_listeners_[i]->mouse_up(&info);
        }
    }
}

void input_manager_t::mouse_move(int x, int y)
{
    input_info_t info(x, y);
    for (size_t i = 0; i < input_listeners_.size(); i++)
    {
        input_listeners_[i]->mouse_move(&info);
    }
}


}
