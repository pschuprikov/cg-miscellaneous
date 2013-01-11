#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "../io_interfaces.h"

namespace tvd
{

struct render_manager_t
    : i_render_manager
{
private:
    render_manager_t(gle::i_engine * engine)
        : engine_(engine)
    {}

public:
    void clear() { renderables_.clear(); }

    void reshape(int width, int height);
    void display();

    // i_render_manager
public:
    void register_renderable(i_renderable * renderable) { renderables_.push_back(renderable); }
    void invalidate();

    static render_manager_t * instance();
private:
    std::vector<i_renderable *> renderables_;
    gle::i_engine * engine_;
};

}

#endif // RENDER_MANAGER_H
