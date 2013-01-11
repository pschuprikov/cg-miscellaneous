#ifndef INVALIDATOR_H
#define INVALIDATOR_H

#include "io_interfaces.h"

namespace tvd
{

struct invalidator_t
{
    invalidator_t()
        : invalid_(false)
    {}

    void treat(i_io_provider * io)
    {
        if (invalid_)
        {
            io->rendering()->invalidate();
            invalid_ = false;
        }
    }

    void invalidate() { invalid_ = true; }

private:
    bool invalid_;
};

}

#endif // INVALIDATOR_H
