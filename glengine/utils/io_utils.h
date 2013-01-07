#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <glecommon.h>

namespace gle
{

namespace utils
{

void load_file_contents(std::string file_name, std::vector<char>& buffer, std::ios_base::openmode mode);

}

}

#endif // IO_UTILS_H
