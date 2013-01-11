#ifndef VORONOI_TEXDRAW_H
#define VORONOI_TEXDRAW_H

#include "stdafx.h"

namespace tvd
{

struct voronoi_texdraw_t
{
    voronoi_texdraw_t();
    ~voronoi_texdraw_t();

    void draw_tex(gle::texture_ptr tex);

private:
    struct impl_t;
private:
    boost::scoped_ptr<impl_t> impl_;
};

}

#endif // VORONOI_TEXDRAW_H
