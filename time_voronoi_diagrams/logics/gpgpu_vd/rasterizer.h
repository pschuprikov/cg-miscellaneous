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
        begin_rasterization();
        gle::samples_passed_query_ptr spq = gle::default_engine()->queries()->create_samples_passed_query();
        gle::primitives_generated_query_ptr pg = gle::default_engine()->queries()->create_primitives_generated_query(0);
        spq->begin_query();
        pg->begin_query();
        for (;beg != end; beg++)
            rasterize(*beg);
        spq->end_query();
        pg->end_query();
        std::cerr << "rasterized:" << spq->samples_passed() << std::endl;
        std::cerr << "primitives: " << pg->primitives_generated() << std::endl;
        end_rasterization();
    }

    void blit_tex();
    gle::texture_ptr tex() const;

private:
    void begin_rasterization();
    void rasterize(newline_data_t const& line);
    void end_rasterization();

private:
    struct impl_t;

private:
    gle::viewport_t old_vp_;

    boost::scoped_ptr<impl_t> impl_;
};

}

#endif // RASTERIZER_H
