#ifndef IFACE_OUTPUT_DATA_H
#define IFACE_OUTPUT_DATA_H

#include "iface_default_data.h"

namespace gle
{

struct iface_output_variable_data_t
    : iface_default_variable_data_t
{
    iface_output_variable_data_t(std::string const& name, GLenum type,
                                  int location, bool is_per_patch, int index)
        : iface_default_variable_data_t(name, type, location)
        , is_per_patch_(is_per_patch)
        , index_(index)
    {}

public:
    bool is_per_patch() const { return is_per_patch_; }
    int index() const { return index_; }

private:
    bool is_per_patch_;
    int index_;
};

struct iface_output_array_data_t
    : iface_default_array_data_t
{
    iface_output_array_data_t(std::string const& name, int size, GLenum type, int location,
                                bool is_per_patch, int index)
        : iface_default_array_data_t(name, size, type, location)
        , is_per_patch_(is_per_patch)
        , index_(index)
    {}

    bool is_per_patch() const { return is_per_patch_; }
    int index() const { return index_; }

    iface_output_variable_data_t const operator[](int idx) const
    {
        return iface_output_variable_data_t(name(), type(), location() + idx, is_per_patch(), index());
    }

private:
    bool is_per_patch_;
    int index_;
};

typedef std::map<std::string, iface_output_variable_data_t> output_vars_map_t;
typedef std::map<std::string, iface_output_array_data_t> output_arrays_map_t;

void fill_output(GLuint pid, output_vars_map_t& output_vars, output_arrays_map_t& output_arrays);

}

#endif // IFACE_OUTPUT_DATA_H
