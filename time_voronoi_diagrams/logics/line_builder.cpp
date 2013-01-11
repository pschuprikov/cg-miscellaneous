#include "line_builder.h"
#include "main_logic.h"

namespace tvd
{

void line_builder_t::reset()
{
    cpu_line_data_.clear();
    line_data_.reset(new line_data_t(glm::vec3(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX,
                                               rand() / (float) RAND_MAX)));
}

void line_builder_t::treat(i_io_provider * io)
{
    invalidator_t::treat(io);

    io->input()->register_input_listener(this);
    io->rendering()->register_renderable(this);
}

void line_builder_t::key_pressed(const i_keyboard_input_info *ev)
{
    if (ev->key_pressed() == 'e')
        proc_->set_main();
}

void line_builder_t::mouse_down(const i_mouse_input_info *ev)
{
    double width = gle::default_engine()->viewport().width();
    double height = gle::default_engine()->viewport().height();

    line_vertex_t new_vtx;
    new_vtx.x = ev->x() / width;
    new_vtx.y = 1 - ev->y() / height;

    cpu_line_data_.push_back(new_vtx);
    line_data_->vtx_data()->buffer_data(gle::BU_static_draw,
        sizeof(line_vertex_t) * cpu_line_data_.size(), &cpu_line_data_[0]);

    invalidate();
}

void line_builder_t::render()
{
    gle::default_engine()->clear_color(glm::vec4(1, 1, 0, 1));
    renderer_->render_line(*line_data_);
}

}
