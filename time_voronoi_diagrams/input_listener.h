#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "stdafx.h"

namespace tvd
{

struct i_input_info
{
    virtual int x() const = 0;
    virtual int y() const = 0;
protected:
    ~i_input_info() {}
};

struct i_keyboard_input_info
    : i_input_info
{
    virtual unsigned char key_pressed() const = 0;
};

enum mouse_button_t { MB_left, MB_right, MB_middle };

struct i_mouse_input_info
    : i_input_info
{
    virtual mouse_button_t button() const = 0;
};

struct i_input_listener
{
    virtual void mouse_up(i_mouse_input_info const * ) {}
    virtual void mouse_down(i_mouse_input_info const * ) {}
    virtual void mouse_move(i_input_info const * ) {}
    virtual void key_pressed(i_keyboard_input_info const * ) {}
};

}

#endif // KEYBOARD_LISTENER_H
