#ifndef IFACE_INPUT_DATA_H
#define IFACE_INPUT_DATA_H

#include "iface_default_data.h"

namespace gle
{

struct iface_input_variable_data_t
    : iface_default_variable_data_t
{
    iface_input_variable_data_t(std::string const& name, GLenum type,
                                  int location, bool is_per_patch)
        : iface_default_variable_data_t(name, type, location)
        , is_per_patch_(is_per_patch)
    {}

public:
    bool is_per_patch() const { return is_per_patch_; }

private:
    bool is_per_patch_;
};

struct iface_input_array_data_t
    : iface_base_array_data_t
{
    iface_input_array_data_t(std::string const& name, int size, GLenum type, int location,
                             bool is_per_patch)
        : iface_base_array_data_t(name, size, type)
        , location_(location)
        , is_per_patch_(is_per_patch)
    {}

    bool is_per_patch() const { return is_per_patch_; }
    int location() const { return location_; }

    iface_input_variable_data_t const operator[](int idx) const
    {
        return iface_input_variable_data_t(name(), type(), location() + idx, is_per_patch());
    }

private:
    int location_;
    bool is_per_patch_;
};

typedef std::map<std::string, iface_input_variable_data_t> input_vars_map_t;
typedef std::map<std::string, iface_input_array_data_t> input_arrays_map_t;

void fill_input(GLuint pid, input_vars_map_t& input_vars, input_arrays_map_t& input_arrays);

}

#endif // IFACE_INPUT_DATA_H
