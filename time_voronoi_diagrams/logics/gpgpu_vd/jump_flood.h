#ifndef JUMP_FLOOD_H
#define JUMP_FLOOD_H

#include "stdafx.h"

namespace tvd
{

struct jump_flood_t
{
    jump_flood_t(float max_distance, float out_velocity);
    ~jump_flood_t();

    void process(gle::texture_ptr tex_rastr, gle::texture_ptr tex_lines_data);

    float max_distance() const { return max_distance_; }
    void set_max_distance(float max_distance) { max_distance_ = max_distance; }

    double outer_velocity() const { return outer_velocity_; }
    void set_outer_velocity(double outer_velocity) { outer_velocity_ = outer_velocity; }

private:
    struct impl_t;

private:
    float max_distance_;
    double outer_velocity_;

    gle::texture_ptr tex_;

    boost::scoped_ptr<impl_t> impl_;
};


}

#endif // JUMP_FLOOD_H
