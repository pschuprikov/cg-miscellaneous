#include <fstream>
#include <string>
#include <algorithm>

#include "stdafx.h"

#include "main_logic.h"
#include "lines_loader.h"

namespace tvd
{

using namespace std;

void lines_loader_t::treat(i_io_provider *io)
{
    main_->voronoi()->set_data(load_lines("lines.dat"));
    main_->voronoi()->process();
    proc_->set_next_logic(main_->voronoi());
}

lines_data_t lines_loader_t::load_lines(std::string const& file_name)
{
    ifstream stin(file_name.c_str());

    int num_lines;
    stin >> num_lines;
    lines_data_t res(num_lines);
    for (int i = 0; i < num_lines; i++)
    {
        stin >> res[i];
    }

    return res;
}

}
