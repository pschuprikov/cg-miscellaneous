#include "line_builder.h"
#include "main_logic.h"

namespace tvd
{

void line_builder_t::reset()
{
    cpu_line_data_.clear();
    line_data_.reset(new line_data_t(glm::vec3(0.5f + rand() / 2 / (float) RAND_MAX, rand() / (float) RAND_MAX,
                                               rand() / (float) RAND_MAX)));
}

void line_builder_t::treat(i_io_provider * io)
{
    invalidator_t::treat(io);

    io->rendering()->register_renderable(main_->lines_builder().get());
    io->input()->register_input_listener(this);
    io->rendering()->register_renderable(this);
}


void line_builder_t::mouse_down(const i_mouse_input_info *ev)
{
    if (ev->button() != tvd::MB_left && ev->button() != tvd::MB_right)
        return;

    line_vertex_t new_vtx = get_vertex(ev);

    if (cpu_line_data_.empty())
        cpu_line_data_.push_back(new_vtx);
    else
        cpu_line_data_.back() = new_vtx;
    cpu_line_data_.push_back(new_vtx);

    line_data_->vtx_data()->buffer_data(gle::BU_dynamic_draw,
        sizeof(line_vertex_t) * cpu_line_data_.size(), &cpu_line_data_[0]);

    if (ev->button() == tvd::MB_right)
    {
        if (!cpu_line_data_.empty())
            main_->lines_builder()->push_line(*line_data_);
        proc_->set_next_logic(main_->lines_builder());
    }

    invalidate();
}

line_vertex_t line_builder_t::get_vertex(const i_input_info *ev)
{
    double width = gle::default_engine()->viewport().width();
    double height = gle::default_engine()->viewport().height();

    line_vertex_t new_vtx;
    new_vtx.x = ev->x() / width;
    new_vtx.y = 1 - ev->y() / height;

    return new_vtx;
}

void line_builder_t::mouse_move(const i_input_info * ev)
{
    if (cpu_line_data_.empty())
        return;
    cpu_line_data_.back() = get_vertex(ev);
    line_data_->vtx_data()->buffer_sub_data(sizeof(line_vertex_t) * (cpu_line_data_.size() - 1),
                                            sizeof(line_vertex_t), &cpu_line_data_[cpu_line_data_.size() - 1]);
    invalidate();
}

void line_builder_t::render()
{
    renderer_->render_line(*line_data_);
}

}
