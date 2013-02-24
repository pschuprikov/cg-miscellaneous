#include "voronoi_diagram.h"

#include "main_logic.h"

namespace tvd
{

voronoi_diagram_t::voronoi_diagram_t(main_logic_t *main)
    : main_(main)
    , proc_(NULL)
    , rastr_(2000, 2000)
    , jfa_(1, 0.1)
{}

void voronoi_diagram_t::treat(i_io_provider * io)
{
    invalidator_t::treat(io);
    io->input()->register_input_listener(this);
    io->rendering()->register_renderable(this);
    io->rendering()->register_renderable(main_->lines_builder().get());
}

void voronoi_diagram_t::key_pressed(const i_keyboard_input_info * ev)
{
    switch(ev->key_pressed())
    {

    case 'e':
        proc_->set_next_logic(main_->lines_builder());
        break;
    case 'p':
    case 'P':
    {
        increase_outer_velocity(ev->key_pressed() == 'P');
        run_jfa();
    } break;
    case 'o':
    case 'O':
    {
        decrease_outer_velocity(ev->key_pressed() == 'O');
        run_jfa();
    } break;

    }
}

void voronoi_diagram_t::increase_outer_velocity(bool presice)
{
    double increase = presice ? 0.001 : 0.02;
    jfa_.set_outer_velocity(std::min(1., jfa_.outer_velocity() + increase));
}

void voronoi_diagram_t::decrease_outer_velocity(bool presice)
{
    double decrease = presice ? 0.001 : 0.02;
    jfa_.set_outer_velocity(std::max(0., jfa_.outer_velocity() - decrease));
}

void voronoi_diagram_t::run_jfa()
{
    gle::time_elapsed_query_ptr teq = gle::default_engine()->queries()->create_time_elapsed_query();
    rastr_.blit_tex();

    teq->begin_query();

    jfa_.process(rastr_.tex());
    gle::default_engine()->memory_barrier(gle::MBB_texture_fetch);

    teq->end_query();

    invalidate();

    std::cerr << "jump_flood_time: " << (teq->time_elapsed_ns() * 1.e-6) << "ms\n";

}

void voronoi_diagram_t::render()
{
    gle::default_engine()->disable(gle::ES_depth_test);
    tex_draw_.draw_tex(rastr_.tex());
    gle::default_engine()->enable(gle::ES_depth_test);
}

void voronoi_diagram_t::process()
{
    if (data_)
    {
        std::vector<newline_data_t> newline_data;

        std::transform(data_->begin(), data_->end(), std::back_inserter(newline_data),
                       boost::bind(&lines_prepare_t::prepare, lines_prep_, _1));

        rastr_.rasterize(newline_data.begin(), newline_data.end());
        run_jfa();
    }
}

}
