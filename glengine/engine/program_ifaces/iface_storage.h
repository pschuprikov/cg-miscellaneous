#ifndef IFACE_STORAGE_H
#define IFACE_STORAGE_H

#include "iface_storage_fwd.h"

#include "iface_default_data.h"
#include "iface_block_data.h"
#include "iface_input_data.h"
#include "iface_output_data.h"

namespace gle
{

struct iface_storage_t
{
    iface_storage_t(GLuint pid);
    ~iface_storage_t();

    iface_default_array_data_t const& array(std::string const& name);
    iface_default_variable_data_t const& var(std::string const& name);
    iface_block_data_ptr const& block(std::string const& name);
    iface_input_variable_data_t const& input_var(std::string const& name);
    iface_input_array_data_t const& input_array(std::string const& name);
    iface_output_variable_data_t const& output_var(std::string const& name);
    iface_output_array_data_t const& output_array(std::string const& name);

private:
    struct storage_impl_t;

private:
    void fill_output();
    void fill_input();
    void fill_default();
    void fill_block(shader_block_type_t type);

    std::pair<iface_block_data_t::block_vars_map_ptr, iface_block_data_t::block_array_map_ptr>
    fill_block_members(int block_idx, shader_block_type_t type);

private:
    GLuint pid_;

    boost::scoped_ptr<storage_impl_t> storage_impl_;
};

}

#endif // IFACE_STORAGE_H
