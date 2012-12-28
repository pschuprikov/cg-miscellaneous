#ifndef ENGINE_H
#define ENGINE_H

#include <glengine.h>

#include "query_object_manager.h"
#include "buffer_object_manager.h"

namespace gle
{
    struct engine
        : i_engine
    {
        engine() { glewInit(); }

        i_query_object_manager * queries() { return &query_manager_; }
        i_buffer_object_manager * buffers() { return &buffer_manager_; }

    private:
        query_object_manager_t query_manager_;
        buffer_object_manager_t buffer_manager_;
    };
}

#endif // ENGINE_H
