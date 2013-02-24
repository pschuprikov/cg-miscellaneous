#ifndef LINE_LOADER_H
#define LINE_LOADER_H

#include "stdafx.h"

#include "../logics.h"
#include "../logics/main_logic_fwd.h"

#include "../lines_common.h"

namespace tvd
{

struct lines_loader_t
    : i_logic
{
    lines_loader_t(main_logic_t * main)
        : main_(main)
        , proc_(nullptr)
    {}

    // i_logic
public:
    void treat(i_io_provider * io);
    void set_processor(i_logic_processor * proc) { proc_ = proc; }

private:
    lines_data_t load_lines(std::string const& file_name);

private:
    main_logic_t * main_;
    i_logic_processor * proc_;
};
typedef boost::shared_ptr<lines_loader_t> lines_loader_ptr;

}

#endif // LINE_LOADER_H
