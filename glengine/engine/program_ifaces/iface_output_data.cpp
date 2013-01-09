#include "iface_output_data.h"

void gle::fill_output(GLuint pid, output_vars_map_t &output_vars, output_arrays_map_t &output_arrays)
{
    GLint num_active;
    GLint max_name_length;
    glGetProgramInterfaceiv(pid, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &num_active);
    glGetProgramInterfaceiv(pid, GL_PROGRAM_OUTPUT, GL_MAX_NAME_LENGTH, &max_name_length);

    std::vector<char> name_buf(max_name_length);
    char * name_buf_ptr = &name_buf[0];

    for (int i = 0; i < num_active; i++)
    {
        glGetProgramResourceName(pid, GL_PROGRAM_OUTPUT, i, max_name_length, NULL, name_buf_ptr);
        static GLenum const props[] = { GL_LOCATION, GL_TYPE, GL_ARRAY_SIZE, GL_IS_PER_PATCH, GL_LOCATION_INDEX };

        static const int num_props = sizeof(props) / sizeof(GLenum);
#pragma pack(push, 1)
        struct params_t
        {
            GLint loc; GLint type; GLint arr_size; GLint is_per_patch; GLint index;
        };
#pragma pack(pop)
        params_t params;

        glGetProgramResourceiv(pid, GL_PROGRAM_OUTPUT, i, num_props, props, num_props,
                               NULL, reinterpret_cast<GLint*>(&params));

        if (params.arr_size != 0)
            output_arrays.insert(std::make_pair(std::string(name_buf_ptr),
                                         iface_output_array_data_t(name_buf_ptr, params.arr_size,
                                                                   params.type, params.loc, params.is_per_patch,
                                                                   params.index)));
        else
            output_vars.insert(std::make_pair(std::string(name_buf_ptr),
                                       iface_output_variable_data_t(name_buf_ptr, params.type,
                                                                    params.loc, params.is_per_patch,
                                                                    params.index)));
    }
}
