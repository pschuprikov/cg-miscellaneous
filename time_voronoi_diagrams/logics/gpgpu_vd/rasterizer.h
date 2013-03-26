#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "lines_prepare.h"
#include "cleaner.h"

namespace tvd
{

struct rasterizer_t
{
    rasterizer_t(int width, int height);
    ~rasterizer_t();

    template<class Iter>
    void rasterize(Iter beg, Iter end)
    {
        gle::image_binding_t binding = gle::default_engine()->textures()->reserve_image_binding();

        int total_segments;
        for (Iter cur = beg; cur != end; ++cur)
            total_segments += cur->count() - 1;

        num_segments_ = total_segments;


        begin_rasterization(total_segments, binding);

        gle::time_elapsed_query_ptr teq = gle::default_engine()->queries()->create_time_elapsed_query();
        teq->begin_query();

        int offset = 0;
        for (;beg != end; beg++)
        {
            rasterize(*beg, offset);
            offset += beg->count() - 1;
        }

        teq->end_query();
        std::cerr << "rasteriazation_time: " << (teq->time_elapsed_ns() * 1.e-6) << "ms\n";

        end_rasterization();

        gle::default_engine()->textures()->release_image_binding(binding);

    }

    void blit_tex();
    gle::texture_ptr tex_rastr() const;
    gle::texture_ptr tex_data() const;

    unsigned int num_segments() const { return num_segments_; }

private:
    void begin_rasterization(size_t num_lines, gle::image_binding_t binding);
    void rasterize(newline_data_t const& line, int offset);
    void end_rasterization();

private:
    struct impl_t;

private:
    gle::viewport_t old_vp_;
    cleaner_t cleaner_;
    unsigned int num_segments_;

    boost::scoped_ptr<impl_t> impl_;
};

}

#endif // RASTERIZER_H
