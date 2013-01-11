#ifndef GLEVIEWPORT_H
#define GLEVIEWPORT_H

#include <glecommon.h>

namespace gle
{

struct viewport_t
{
    viewport_t()
        : x_(0), y_(0), width_(0), height_(0)
    {}

    viewport_t(int x, int y, int width, int height)
        : x_(x), y_(y), width_(width), height_(height)
    {}

    int x() const { return x_; }
    int y() const { return y_; }
    int width() const { return width_; }
    int height() const { return height_; }

private:
    int x_;
    int y_;
    int width_;
    int height_;
};

}

#endif // GLEVIEWPORT_H
