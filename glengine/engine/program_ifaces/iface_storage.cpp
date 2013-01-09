#include "iface_storage.h"

namespace gle
{

struct iface_storage_t::storage_impl_t
{
    std::map<std::string, iface_default_variable_data_t> vars;
    std::map<std::string, iface_default_array_data_t> arrays;
    std::map<std::string, iface_block_data_ptr> blocks;
    input_vars_map_t input_vars;
    input_arrays_map_t input_arrays;
    output_vars_map_t output_vars;
    output_arrays_map_t output_arrays;
};

iface_storage_t::iface_storage_t(GLuint pid)
    : pid_(pid)
    , storage_impl_(new storage_impl_t())
{
    fill_input();
    fill_output();
    fill_default();
    fill_block(SBT_uniform);
    fill_block(SBT_storage);
}

iface_storage_t::~iface_storage_t() {}


void iface_storage_t::fill_input()
{
    gle::fill_input(pid_, storage_impl_->input_vars, storage_impl_->input_arrays);
}

void iface_storage_t::fill_output()
{
    gle::fill_output(pid_, storage_impl_->output_vars, storage_impl_->output_arrays);
}

iface_default_array_data_t const& iface_storage_t::array(std::string const& name)
{
    return storage_impl_->arrays.at(name);
}

iface_default_variable_data_t const& iface_storage_t::var(std::string const& name)
{
    return storage_impl_->vars.at(name);
}

iface_block_data_ptr const& iface_storage_t::block(std::string const& name)
{
    return storage_impl_->blocks.at(name);
}

iface_input_variable_data_t const& iface_storage_t::input_var(std::string const& name)
{
    return storage_impl_->input_vars.at(name);
}

iface_input_array_data_t const& iface_storage_t::input_array(std::string const& name)
{
    return storage_impl_->input_arrays.at(name);
}

iface_output_variable_data_t const& iface_storage_t::output_var(std::string const& name)
{
    return storage_impl_->output_vars.at(name);
}

iface_output_array_data_t const& iface_storage_t::output_array(std::string const& name)
{
    return storage_impl_->output_arrays.at(name);
}


void iface_storage_t::fill_default()
{
    GLint num_active;
    GLint max_name_length;
    glGetProgramInterfaceiv(pid_, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_active);
    glGetProgramInterfaceiv(pid_, GL_UNIFORM, GL_MAX_NAME_LENGTH, &max_name_length);

    std::vector<char> name_buf(max_name_length);
    char * name_buf_ptr = &name_buf[0];

    for (int i = 0; i < num_active; i++)
    {
        glGetProgramResourceName(pid_, GL_UNIFORM, i, max_name_length, NULL, name_buf_ptr);
        GLenum props[] = { GL_BLOCK_INDEX, GL_ATOMIC_COUNTER_BUFFER_INDEX,
                         GL_LOCATION, GL_TYPE, GL_ARRAY_SIZE };

#pragma pack(push, 1)
        struct params_t
        {
            GLint block_idx; GLint atomic_idx; GLint loc; GLint type; GLint arr_size;
        };
#pragma pack(pop)
        params_t params;

        glGetProgramResourceiv(pid_, GL_UNIFORM, i, 5, props, 5, NULL, reinterpret_cast<GLint*>(&params));

        if (params.block_idx != -1 || params.atomic_idx != -1)
            continue;
        if (params.arr_size != 0)
            storage_impl_->arrays.insert(std::make_pair(std::string(name_buf_ptr),
                                                 iface_default_array_data_t(name_buf_ptr, params.arr_size,
                                                                            params.type, params.loc)));
        else
            storage_impl_->vars.insert(std::make_pair(std::string(name_buf_ptr),
                                                 iface_default_variable_data_t(name_buf_ptr, params.type,
                                                                               params.loc)));
    }
}

std::pair<iface_block_data_t::block_vars_map_ptr, iface_block_data_t::block_array_map_ptr>
iface_storage_t::fill_block_members(int block_idx, shader_block_type_t type)
{
    static GLenum const idx_prop = GL_ACTIVE_VARIABLES;
    static GLenum const num_vars_prop = GL_NUM_ACTIVE_VARIABLES;

    iface_block_data_t::block_vars_map_ptr vars_(new iface_block_data_t::block_vars_map_t());
    iface_block_data_t::block_array_map_ptr arrays_(new iface_block_data_t::block_array_map_t());

    GLint num_vars;
    GLint max_name_length;
    glGetProgramResourceiv(pid_, sbt2gliface(type), block_idx, 1, &num_vars_prop, 1, NULL, &num_vars);
    glGetProgramInterfaceiv(pid_, sbt2glvar(type), GL_MAX_NAME_LENGTH, &max_name_length);

    if (num_vars == 0)
        return std::make_pair(vars_, arrays_);

    std::vector<GLint> indicies(num_vars);
    glGetProgramResourceiv(pid_, sbt2gliface(type), block_idx, 1, &idx_prop, num_vars, NULL, &indicies[0]);

    std::vector<char> name_buf(max_name_length);
    char * name_buf_ptr = &name_buf[0];

    for (int i = 0; i < num_vars; i++)
    {
        glGetProgramResourceName(pid_, sbt2glvar(type), indicies[i], max_name_length, NULL, name_buf_ptr);
        GLenum props[] = { GL_OFFSET, GL_ARRAY_STRIDE, GL_TYPE, GL_ARRAY_SIZE,
                           GL_TOP_LEVEL_ARRAY_SIZE, GL_TOP_LEVEL_ARRAY_STRIDE };
#pragma pack(push, 1)
        struct params_t
        {
            GLint offset; GLint arr_stride; GLint type; GLint arr_size; GLint tl_arr_size; GLint tl_arr_stride;
        };
#pragma pack(pop)

        static const int num_props = sizeof(props) / sizeof(GLenum);

        params_t params;
        glGetProgramResourceiv(pid_, sbt2glvar(type), indicies[i], num_props, props, num_props, NULL,
                               reinterpret_cast<GLint*>(&params));

        if (params.tl_arr_size != 1) // indeed top level array
            arrays_->insert(std::make_pair(std::string(name_buf_ptr),
                iface_block_array_data_t(name_buf_ptr, params.tl_arr_size, params.type,
                                         params.tl_arr_stride, params.offset)));
        else if (params.arr_size == 0)
            vars_->insert(std::make_pair(std::string(name_buf_ptr),
                iface_block_variable_data_t(name_buf_ptr, params.type, params.offset)));
        else
            arrays_->insert(std::make_pair(std::string(name_buf_ptr),
                iface_block_array_data_t(name_buf_ptr, params.arr_size, params.type,
                                         params.arr_stride, params.offset)));
    }
    return std::make_pair(vars_, arrays_);
}


void iface_storage_t::fill_block(shader_block_type_t type)
{
    GLint num_active;
    GLint max_name_length;
    glGetProgramInterfaceiv(pid_, sbt2gliface(type), GL_ACTIVE_RESOURCES, &num_active);
    glGetProgramInterfaceiv(pid_, sbt2gliface(type), GL_MAX_NAME_LENGTH, &max_name_length);

    std::vector<char> name_buf(max_name_length);
    char * name_buf_ptr = &name_buf[0];

    for (int i = 0; i < num_active; i++)
    {
        glGetProgramResourceName(pid_, sbt2gliface(type), i, max_name_length, NULL, name_buf_ptr);
        std::pair<iface_block_data_t::block_vars_map_ptr, iface_block_data_t::block_array_map_ptr>
                members = fill_block_members(i, type);

        GLenum props[] = { GL_BUFFER_DATA_SIZE, GL_BUFFER_BINDING };
        GLint params[2];
        glGetProgramResourceiv(pid_, sbt2gliface(type), i, 1, props, 1, NULL, params);

        storage_impl_->blocks.insert(std::make_pair(std::string(name_buf_ptr),
            iface_block_data_ptr(new iface_block_data_t(name_buf_ptr, i,
                params[0], type, members.first, members.second, params[1]))));
    }
}



}
