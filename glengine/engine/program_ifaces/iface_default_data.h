#ifndef IFACE_DATA_H
#define IFACE_DATA_H

#include "iface_common_data.h"

namespace gle
{

struct iface_default_variable_data_t
    : iface_base_variable_data_t
{
public:
    iface_default_variable_data_t(std::string const& name, GLenum type,
                                int location)
        : iface_base_variable_data_t(name, type)
        , location_(location)
    {}

    int location() const { return location_; }

private:
    int location_;
};

struct iface_default_array_data_t
    : iface_base_array_data_t
{
    iface_default_array_data_t(std::string const& name, int size, GLenum type, int location)
        : iface_base_array_data_t(name, size, type)
        , location_(location)
    {}

    int location() const { return location_; }

    iface_default_variable_data_t const operator[](int idx) const
    {
        return iface_default_variable_data_t(name(), type(), location() + idx);
    }

private:
    int location_;
};

}

#endif // IFACE_DATA_H
