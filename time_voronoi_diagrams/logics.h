#ifndef LOGIC_H
#define LOGIC_H

#include "stdafx.h"

#include "io_interfaces.h"

namespace tvd
{

struct i_logic_processor;
struct i_logic;
typedef boost::shared_ptr<i_logic> logic_ptr;

struct i_logic_processor
{
    virtual void set_next_logic(logic_ptr logic) = 0;
    virtual void set_main() = 0;
};

struct i_logic
{
    virtual void treat(i_io_provider * io) = 0;
    virtual void set_processor(i_logic_processor * proc) = 0;

    virtual ~i_logic() {}
};

}

#endif // LOGIC_H
