#ifndef LOGIC_PROCESSOR_H
#define LOGIC_PROCESSOR_H

#include "../logics.h"

namespace tvd
{

struct logic_processor_t
    : i_logic_processor
{
public:
    logic_processor_t(logic_ptr main)
        : main_(main)
    {
        main_->set_processor(this);
        set_main();
    }

    void treat(i_io_provider * io);

    // i_logic_processor
public:
    void set_next_logic(logic_ptr logic)
    {
        if (logic)
        {
            logic->set_processor(this);
            next_ = logic;
        }
    }

    void set_main() { next_ = main_; }


private:
    logic_ptr main_;

    logic_ptr current_;
    boost::optional<logic_ptr> next_;
};

}

#endif // LOGIC_PROCESSOR_H
