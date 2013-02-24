#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "io_utils.h"

namespace gle
{

namespace bfs = boost::filesystem;

void utils::load_file_contents(std::string file_name, std::vector<char> &buffer, std::ios_base::openmode mode)
{
    bfs::ifstream stin(bfs::current_path() / file_name, mode);
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
