#include "engine.h"

gle::i_engine * gle::default_engine()
{
    static engine_t eng;
    return &eng;
}

namespace gle
{

void engine_t::memory_barrier(memory_barrier_bit_t barriers)
{
    glMemoryBarrier(barriers);
}

void engine_t::clear(bit_plane_bit_t buffers_mask)
{
    glClear(buffers_mask);
}

void engine_t::clear_color(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

}
