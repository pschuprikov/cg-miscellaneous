#include "iface_input_data.h"

void gle::fill_input(GLuint pid, input_vars_map_t &input_vars, input_arrays_map_t &input_arrays)
{
    GLint num_active;
    GLint max_name_length;
    glGetProgramInterfaceiv(pid, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &num_active);
    glGetProgramInterfaceiv(pid, GL_PROGRAM_INPUT, GL_MAX_NAME_LENGTH, &max_name_length);

    std::vector<char> name_buf(max_name_length);
    char * name_buf_ptr = &name_buf[0];

    for (int i = 0; i < num_active; i++)
    {
        glGetProgramResourceName(pid, GL_PROGRAM_INPUT, i, max_name_length, NULL, name_buf_ptr);
        static GLenum const props[] = { GL_LOCATION, GL_TYPE, GL_ARRAY_SIZE, GL_IS_PER_PATCH };

        static const int num_props = sizeof(props) / sizeof(GLenum);
#pragma pack(push, 1)
        struct params_t
        {
            GLint loc; GLint type; GLint arr_size; GLint is_per_patch;
        };
#pragma pack(pop)
        params_t params;

        glGetProgramResourceiv(pid, GL_PROGRAM_INPUT, i, num_props, props, num_props,
                               NULL, reinterpret_cast<GLint*>(&params));

        if (params.arr_size != 0)
            input_arrays.insert(std::make_pair(std::string(name_buf_ptr),
                                         iface_input_array_data_t(name_buf_ptr, params.arr_size,
                                                                  params.type, params.loc, params.is_per_patch)));
        else
            input_vars.insert(std::make_pair(std::string(name_buf_ptr),
                                       iface_input_variable_data_t(name_buf_ptr, params.type,
                                                                     params.loc, params.is_per_patch)));
    }

}
