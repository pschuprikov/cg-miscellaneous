#ifndef SEGMENTS_BUILDER_H
#define SEGMENTS_BUILDER_H

#include "../logics.h"
#include "main_logic_fwd.h"
#include "line_builder.h"

#include "invalidator.h"
#include "../renderers/line_renderer.h"

namespace tvd
{


struct lines_builder_t
    : i_logic
    , i_renderable
    , i_input_listener
    , private invalidator_t
{
    lines_builder_t(main_logic_t * main);

    void reset() { lines_.clear(); }
    void push_line(line_data_t const& data) { lines_.push_back(data); }

    // i_logic
public:
    void treat(i_io_provider * io);
    void set_processor(i_logic_processor * proc) { proc_ = proc; }

    // i_renderable
public:
    void render();

    // i_input_listener
public:
    void key_pressed(const i_keyboard_input_info * ev);

private:
    main_logic_t * main_;

    i_logic_processor * proc_;

    line_renderer_ptr render_;
    line_builder_ptr line_builder_;

    lines_data_t lines_;
};
typedef boost::shared_ptr<lines_builder_t> lines_builder_ptr;

}

#endif // SEGMENTS_BUILDER_H
