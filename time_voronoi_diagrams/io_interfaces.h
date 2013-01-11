#ifndef IO_INTERFACES_H
#define IO_INTERFACES_H

#include "input_listener.h"
#include "renderable.h"

namespace tvd
{
    struct i_input_manager
    {
        virtual void register_input_listener(i_input_listener * listener) = 0;
    };

    struct i_render_manager
    {
        virtual void register_renderable(i_renderable * renderable) = 0;
        virtual void invalidate() = 0;
    };

    struct i_io_provider
    {
        virtual i_input_manager * input() = 0;
        virtual i_render_manager * rendering() = 0;
    };
}

#endif // UI_INTERACTION_H
