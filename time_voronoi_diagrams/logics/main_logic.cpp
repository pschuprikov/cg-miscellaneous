#include "main_logic.h"

namespace tvd
{

void main_logic_t::treat(i_io_provider * io)
{
    io->input()->register_input_listener(this);
    io->rendering()->register_renderable(this);
    if (!line_builder_)
    {
        line_renderer_ptr renderer;
        try
        {
            renderer.reset(new line_renderer_t());
        }
        catch (gle::compilation_failed_exception_t const& cfe)
        {
            std::cerr << cfe.name() << std::endl;
            std::cerr << cfe.reason() << std::endl;
        }

        line_builder_.reset(new line_builder_t(this, renderer));
    }
}

void main_logic_t::key_pressed(const i_keyboard_input_info *ev)
{
    if (ev->key_pressed() == 'e')
    {
        line_builder_->reset();
        proc_->set_next_logic(line_builder_);
    }
}

}
