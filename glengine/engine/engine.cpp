#include "engine.h"

gle::i_engine * gle::default_engine()
{
    static engine eng;
    return &eng;
}
