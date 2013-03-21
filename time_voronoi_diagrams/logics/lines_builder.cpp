#include "lines_builder.h"

#include "main_logic.h"

namespace tvd
{

lines_builder_t::lines_builder_t(main_logic_t *main)
    : main_(main)
    , proc_(NULL)
    , render_(new line_renderer_t())
    , line_builder_(new line_builder_t(main_, render_))
{}

void lines_builder_t::treat(i_io_provider * io)
{
    io->input()->register_input_listener(this);
    io->rendering()->register_renderable(this);
}

void lines_builder_t::render()
{
    gle::default_engine()->disable(gle::ES_depth_test);
    for (size_t i = 0; i < lines_.size(); i++)
        render_->render_line(lines_[i]);
    gle::default_engine()->enable(gle::ES_depth_test);
}

void lines_builder_t::key_pressed(const i_keyboard_input_info * ev)
{
    if (ev->key_pressed() == 'n')
    {
        line_builder_->reset();
        proc_->set_next_logic(line_builder_);
    }
    else if (ev->key_pressed() == 'q')
    {
        main_->voronoi()->set_data(lines_);
        main_->voronoi()->process();
        proc_->set_next_logic(main_->voronoi());
    }
    else if (ev->key_pressed() == 'c')
    {
        reset();
    }
}

}
