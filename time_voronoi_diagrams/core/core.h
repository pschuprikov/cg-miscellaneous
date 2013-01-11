#ifndef CORE_H
#define CORE_H

#include "../logics.h"
#include "logic_processor.h"

namespace tvd
{

struct core_t
    : i_io_provider
{
private:
    core_t() {}

public:
    // logic should not start before
    void run(logic_ptr main_logic, int x, int y, int width, int height, const std::string &title);
    void treat();

    // i_io_provider
public:
    i_input_manager * input();
    i_render_manager * rendering();

public:
    static core_t * instance();

private:
    boost::scoped_ptr<logic_processor_t> logics_;
};

}

#endif // CORE_H
