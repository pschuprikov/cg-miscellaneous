#include <fstream>

#include "io_utils.h"

namespace gle
{

void utils::load_file_contents(std::string file_name, std::vector<char> &buffer, std::ios_base::openmode mode)
{
    std::ifstream stin(file_name.c_str(), mode);
    if (!stin)
        throw std::invalid_argument("file not found!");
    stin.seekg(0, std::ios_base::end);
    int len = stin.tellg();
    stin.seekg(0, std::ios_base::beg);

    buffer.resize(len);
    if (len > 0)
        stin.read(&buffer[0], len);
}


}
