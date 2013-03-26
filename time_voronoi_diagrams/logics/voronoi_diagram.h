#ifndef VORONOI_DIAGRAM_H
#define VORONOI_DIAGRAM_H

#include "../logics.h"

#include "main_logic_fwd.h"
#include "lines_builder.h"
#include "invalidator.h"

#include "gpgpu_vd/lines_prepare.h"
#include "gpgpu_vd/rasterizer.h"
#include "gpgpu_vd/voronoi_texdraw.h"
#include "gpgpu_vd/jump_flood.h"
#include "gpgpu_vd/naive.h"

namespace tvd
{

struct voronoi_diagram_t
    : i_logic
    , i_input_listener
    , i_renderable
    , private invalidator_t
{
    voronoi_diagram_t(main_logic_t * main);

    void set_data(lines_data_t const& data) { data_.reset(new lines_data_t(data)); }
    void process();

    double error_percent();

    // i_logic
public:
    void treat(i_io_provider * io);
    void set_processor(i_logic_processor * proc) { proc_ = proc; }

    // i_input_listener
public:
    void key_pressed(const i_keyboard_input_info *ev);

    // i_renderable
public:
    void render();

private:
    void increase_outer_velocity(bool presice = false);
    void decrease_outer_velocity(bool presice = false);

    void run_jfa();
    void run_naive();

private:
    boost::scoped_ptr<lines_data_t> data_;
    std::vector<newline_data_t> newlines_data_;

    main_logic_t *      main_;
    i_logic_processor * proc_;

    lines_prepare_t lines_prep_;
    rasterizer_t         rastr_;
    voronoi_texdraw_t tex_draw_;
    jump_flood_t           jfa_;
    naive_t              naive_;

    bool use_naive_;
};
typedef boost::shared_ptr<voronoi_diagram_t> voronoi_diagram_ptr;

}

#endif // VORONOI_DIAGRAM_H
