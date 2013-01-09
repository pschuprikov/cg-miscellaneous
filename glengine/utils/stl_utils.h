#ifndef STL_UTILS_H
#define STL_UTILS_H

#include <glecommon.h>

namespace gle
{

namespace utils
{

template<class T>
T * raw_ptr(std::vector<T>& v)
{
    return v.empty() ? NULL : &v[0];
}

}

}

#endif // STL_UTILS_H
