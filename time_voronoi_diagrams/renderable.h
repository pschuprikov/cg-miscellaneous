#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "stdafx.h"

namespace tvd
{

struct i_renderable
{
    virtual void render() = 0;
};

}

#endif // RENDERABLE_H
