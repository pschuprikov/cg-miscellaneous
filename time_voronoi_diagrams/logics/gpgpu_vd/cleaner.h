#ifndef CLEANER_H
#define CLEANER_H

#include "stdafx.h"

namespace tvd
{

struct cleaner_t
{
    cleaner_t();

    void clean_tex(gle::texture_ptr tex, unsigned int value);
private:
    gle::program_ptr prg_;
    gle::shader_variable_ptr clear_value_;
    gle::shader_variable_ptr img_clear_;
};

}

#endif // CLEANER_H
