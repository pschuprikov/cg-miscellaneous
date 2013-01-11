#ifndef JUMP_FLOOD_H
#define JUMP_FLOOD_H

#include "stdafx.h"

namespace tvd
{

struct jump_flood_t
{
    jump_flood_t(float max_distance, float out_velocity);
    ~jump_flood_t();

    void process(gle::texture_ptr tex);

    float max_distance() const { return max_distance_; }
    void set_max_distance(float max_distance) { max_distance_ = max_distance; }

    float outer_velocity() const { return outer_velocity_; }
    void set_outer_velocity(float outer_velocity) { outer_velocity_ = outer_velocity; }

private:
    struct impl_t;

private:
    float max_distance_;
    float outer_velocity_;

    boost::scoped_ptr<impl_t> impl_;
};


}

#endif // JUMP_FLOOD_H
