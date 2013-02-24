#include "main_logic.h"

namespace tvd
{

void main_logic_t::treat(i_io_provider * io)
{
    io->input()->register_input_listener(this);
    if (!lines_builder_)
    {
        lines_builder_.reset(new lines_builder_t(this));
        voronoi_.reset(new voronoi_diagram_t(this));
    }
}

void main_logic_t::key_pressed(const i_keyboard_input_info *ev)
{
    if (ev->key_pressed() == 'e')
    {
        lines_builder_->reset();
        proc_->set_next_logic(lines_builder_);
    }
}

}
