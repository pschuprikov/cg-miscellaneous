#include "logic_processor.h"

namespace tvd
{

void logic_processor_t::treat(i_io_provider * io)
{
    if (next_)
    {
        current_ = *next_;
        next_.reset();
        io->rendering()->invalidate();
    }
    current_->treat(io);
}

}
