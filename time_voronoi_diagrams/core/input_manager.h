#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "stdafx.h"
#include "../io_interfaces.h"

namespace tvd
{

struct input_manager_t
    : i_input_manager
{
private:
    input_manager_t() {}

public:
    void clear() { input_listeners_.clear(); }

    // i_input_manager

public:
    void keyboard_event(unsigned char key, int x, int y);
    void mouse_event(int button, int state, int x, int y);
    void mouse_move(int x, int y);

    void register_input_listener(i_input_listener * listener)
    {
        input_listeners_.push_back(listener);
    }

public:
    static input_manager_t * instance();

private:
    std::vector<i_input_listener *> input_listeners_;
};

}

#endif // UI_INTERACTION_H
