#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "lines_prepare.h"

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

        begin_rasterization(total_segments, binding);
        //gle::samples_passed_query_ptr spq = gle::default_engine()->queries()->create_samples_passed_query();
        //gle::primitives_generated_query_ptr pg = gle::default_engine()->queries()->create_primitives_generated_query(0);
        //spq->begin_query();
        //pg->begin_query();

        int offset = 0;
        for (;beg != end; beg++)
        {
            rasterize(*beg, offset);
            offset += beg->count() - 1;
        }

        //spq->end_query();
        //pg->end_query();
        //std::cerr << "rasterized:" << spq->samples_passed() << std::endl;
        //std::cerr << "primitives: " << pg->primitives_generated() << std::endl;
        end_rasterization();
        gle::default_engine()->textures()->release_image_binding(binding);

    }

    void blit_tex();
    gle::texture_ptr tex_rastr() const;
    gle::texture_ptr tex_data() const;

private:
    void begin_rasterization(size_t num_lines, gle::image_binding_t binding);
    void rasterize(newline_data_t const& line, int offset);
    void end_rasterization();

private:
    struct impl_t;

private:
    gle::viewport_t old_vp_;

    boost::scoped_ptr<impl_t> impl_;
};

}

#endif // RASTERIZER_H
