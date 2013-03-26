#include "voronoi_diagram.h"

#include "main_logic.h"

namespace tvd
{

namespace
{
const int g_width  = 1024;
const int g_height = 1024;
}

voronoi_diagram_t::voronoi_diagram_t(main_logic_t *main)
    : main_(main)
    , proc_(NULL)
    , rastr_(g_width, g_height)
    , jfa_(5, 0.1)
    , use_naive_(false)
{
}

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
        if (use_naive_) run_naive(); else run_jfa();
    } break;
    case 'o':
    case 'O':
    {
        decrease_outer_velocity(ev->key_pressed() == 'O');
        if (use_naive_) run_naive(); else run_jfa();
    } break;
    case 'n':
    {
        use_naive_ = !use_naive_;
        if (use_naive_) run_naive(); else run_jfa();
    } break;
    case 'a':
        std::cerr << "errors: " << error_percent() << "%\n";
        break;

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
    rastr_.blit_tex();

    jfa_.process(rastr_.tex_rastr(), rastr_.tex_data());

    gle::default_engine()->memory_barrier(gle::MBB_texture_fetch);

    invalidate();
}

double voronoi_diagram_t::error_percent()
{
    std::vector<unsigned short int> jfa_res(g_width * g_height);
    std::vector<unsigned short int> naive_res(g_width * g_height);

    rastr_.blit_tex();
    jfa_.process(rastr_.tex_rastr(), rastr_.tex_data());
    gle::default_engine()->memory_barrier(gle::MBB_all);
    rastr_.tex_rastr()->get_image(0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, &jfa_res[0]);
    rastr_.blit_tex();
    naive_.process(rastr_.tex_rastr(), rastr_.tex_data(), jfa_.max_distance(),
        jfa_.outer_velocity(), rastr_.num_segments());
    gle::default_engine()->memory_barrier(gle::MBB_all);
    rastr_.tex_rastr()->get_image(0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, &naive_res[0]);

    unsigned int num_errors = 0;
    for (size_t i = 0; i < jfa_res.size(); i++)
        if (jfa_res[i] != naive_res[i]) num_errors++;
    return num_errors * 100 / (double)(g_width * g_height);
}

void voronoi_diagram_t::run_naive()
{
    rastr_.blit_tex();

    naive_.process(rastr_.tex_rastr(), rastr_.tex_data(), jfa_.max_distance(),
        jfa_.outer_velocity(), rastr_.num_segments());

    invalidate();
}

void voronoi_diagram_t::render()
{
    gle::default_engine()->disable(gle::ES_depth_test);
    tex_draw_.draw_tex(rastr_.tex_rastr(), rastr_.tex_data());
    gle::default_engine()->enable(gle::ES_depth_test);
}

void voronoi_diagram_t::process()
{
    if (data_)
    {
        newlines_data_.clear();
        std::transform(data_->begin(), data_->end(), std::back_inserter(newlines_data_),
                       boost::bind(&lines_prepare_t::prepare, lines_prep_, _1));

        rastr_.rasterize(newlines_data_.begin(), newlines_data_.end());

        if (use_naive_)
            run_naive();
        else
        {
            run_jfa();
        }

    }
}

}
