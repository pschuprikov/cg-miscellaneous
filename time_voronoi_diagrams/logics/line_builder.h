#ifndef SEGMENT_BUILDER_H
#define SEGMENT_BUILDER_H

#include "stdafx.h"
#include "../logics.h"
#include "../renderers/line_renderer.h"
#include "invalidator.h"

#include "main_logic_fwd.h"

namespace tvd
{

struct line_builder_t
    : i_logic
    , i_input_listener
    , i_renderable
    , private invalidator_t
{
    line_builder_t(main_logic_t * main, line_renderer_ptr renderer)
        : main_(main)
        , proc_(NULL)
        , renderer_(renderer)
    {}

public:
    void reset();

    // i_logic
public:
    void treat(i_io_provider * io);
    void set_processor(i_logic_processor * proc) { proc_ = proc; }

    // i_input_listener
public:
    void mouse_down(const i_mouse_input_info *ev);
    void mouse_move(const i_input_info * ev);

    // i_renderable
public:
    void render();

private:
    line_vertex_t get_vertex(const i_input_info *ev);

private:
    boost::scoped_ptr<line_data_t> line_data_;
    std::vector<line_vertex_t> cpu_line_data_;

    main_logic_t * main_;
    i_logic_processor * proc_;

    line_renderer_ptr renderer_;
};
typedef boost::shared_ptr<line_builder_t> line_builder_ptr;

}

#endif // SEGMENT_BUILDER_H
