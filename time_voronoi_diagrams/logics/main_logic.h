#ifndef MAIN_LOGIC_H
#define MAIN_LOGIC_H

#include "main_logic_fwd.h"

#include "../logics.h"

#include "lines_builder.h"
#include "voronoi_diagram.h"

namespace tvd
{

struct main_logic_t
    : i_logic
    , i_input_listener
{
    main_logic_t()
        : proc_(0)
    {}

    lines_builder_ptr lines_builder() const { return lines_builder_; }
    voronoi_diagram_ptr voronoi() const { return voronoi_; }

    void treat(i_io_provider * io);
    void set_processor(i_logic_processor * proc) { proc_ = proc; }

    void key_pressed(const i_keyboard_input_info *ev);

private:
    i_logic_processor * proc_;

    lines_builder_ptr lines_builder_;
    voronoi_diagram_ptr voronoi_;
};

typedef boost::shared_ptr<main_logic_t> main_logic_ptr;

}

#endif // MAIN_LOGIC_H
