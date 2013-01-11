#include "lines_prepare.h"

namespace tvd
{

newline_data_t lines_prepare_t::prepare(line_data_t const& data)
{
    std::vector<newline_vertex_t> newline(data.count());

    data.vtx_data()->map_buffer(GL_READ_ONLY);
    line_vertex_t const * const vertices = reinterpret_cast<line_vertex_t const *>(data.vtx_data()->map_pointer());

    double distance_so_far = 0;
    for (int i = 0; i < data.count(); i++)
    {
        line_vertex_t const& fst = vertices[i];
        newline[i] = newline_vertex_t(fst.x, fst.y, distance_so_far);

        if (i < data.count() - 1)
        {
            line_vertex_t const& snd = vertices[i + 1];

            glm::dvec2 fst_pt(fst.x, fst.y);
            glm::dvec2 snd_pt(snd.x, snd.y);

            distance_so_far += glm::distance(fst_pt, snd_pt);
        }
    }

    gle::buffer_ptr segments_buf = gle::default_engine()->buffers()->create_buffer();
    segments_buf->buffer_data(gle::BU_static_draw, sizeof(newline_vertex_t) * newline.size(), &newline[0]);

    data.vtx_data()->unmap_buffer();

    return newline_data_t(data.color(), segments_buf);
}

}
