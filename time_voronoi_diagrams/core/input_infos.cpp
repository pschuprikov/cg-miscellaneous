#include "stdafx.h"

#include "input_infos.h"

namespace tvd
{

input_info_t::input_info_t(int x, int y)
    : x_(x), y_(y)
{
    int mods = glutGetModifiers();
    alt_ = ((mods & GLUT_ACTIVE_ALT) == GLUT_ACTIVE_ALT);
    shift_ = ((mods & GLUT_ACTIVE_SHIFT) == GLUT_ACTIVE_SHIFT);
    ctrl_ = ((mods & GLUT_ACTIVE_CTRL) == GLUT_ACTIVE_CTRL);
}

keyborad_input_info_t::keyborad_input_info_t(char key, int x, int y)
    : info_(x, y)
    , key_(key)
{}

mouse_input_info_t::mouse_input_info_t(int button, int x, int y)
    : info_(x, y)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON : btn_ = MB_left;
    case GLUT_RIGHT_BUTTON : btn_ = MB_right;
    case GLUT_MIDDLE_BUTTON : btn_ = MB_middle;
    }
}

}
