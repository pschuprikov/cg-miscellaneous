#ifndef GLENGINHE_H
#define GLENGINHE_H

#include <glm/glm.hpp>

#include <glequery_object_manager.h>
#include <glebuffer_object_manager.h>

namespace gle
{
    struct i_engine
    {
        virtual i_query_object_manager * queries() = 0;
        virtual i_buffer_object_manager * buffers() = 0;

        virtual ~i_engine() {}
    };

    i_engine * default_engine();
}

#endif // GLENGINHE_H
