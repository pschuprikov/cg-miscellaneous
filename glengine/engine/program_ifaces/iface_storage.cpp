#include "iface_storage.h"

namespace gle
{

struct iface_storage_t::storage_impl_t
{
    std::map<std::string, iface_default_variable_data_t> vars;
    std::map<std::string, iface_default_array_data_t> arrays;
    std::map<std::string, iface_block_data_ptr> blocks;
};

iface_storage_t::iface_storage_t(GLuint pid)
    : pid_(pid)
    , storage_impl_(new storage_impl_t())
{
    fill_default();
    fill_block(SBT_uniform);
    fill_block(SBT_storage);
}

iface_storage_t::~iface_storage_t() {}

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
        GLenum props[] = { GL_OFFSET, GL_ARRAY_STRIDE, GL_TYPE, GL_ARRAY_SIZE };
#pragma pack(push, 1)
        struct params_t
        {
            GLint offset; GLint arr_stride; GLint type; GLint arr_size;
        };
#pragma pack(pop)

        params_t params;
        glGetProgramResourceiv(pid_, sbt2glvar(type), indicies[i], 4, props, 4, NULL,
                               reinterpret_cast<GLint*>(&params));

        if (params.arr_size > 0)
            arrays_->insert(std::make_pair(std::string(name_buf_ptr),
                iface_block_array_data_t(name_buf_ptr, params.arr_size, params.type,
                                         params.arr_stride, params.offset)));
        else
            vars_->insert(std::make_pair(std::string(name_buf_ptr),
                iface_block_variable_data_t(name_buf_ptr, params.type, params.offset)));
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
