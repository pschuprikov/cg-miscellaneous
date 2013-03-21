#include "rasterizer.h"
#include "renderers/drawing_utils.h"

namespace tvd
{

struct rasterizer_t::impl_t
{
    gle::vertex_attrib_binding_t vtx_binding;

    gle::program_ptr prg;
    gle::program_ptr clean_prg;

    gle::vertex_array_ptr vao;
    gle::framebuffer_ptr fbo;

    gle::texture_ptr lines_data;

    impl_t(int width, int height)
    {
        load_program();

        lines_data = gle::default_engine()->textures()->create_texture(gle::TT_1d);
        lines_data->set_mag_filter(gle::TMAGF_nearest);
        lines_data->set_min_filter(gle::TMINF_nearest);

        setup_vao();
        setup_fbo(width, height);
    }

private:

    void load_program()
    {
        prg = gle::default_engine()->programs()->create_program("rasterizer");
        try
        {
            gle::shader_ptr fs = gle::default_engine()->programs()->load_shader(
                "shaders/rasterizer_fs.glsl",
                gle::ST_fragment);
            gle::shader_ptr gs = gle::default_engine()->programs()->load_shader(
                "shaders/rasterizer_gs.glsl",
                gle::ST_geometry);
            gle::shader_ptr vs = gle::default_engine()->programs()->load_shader(
                "shaders/rasterizer_vs.glsl",
                gle::ST_vertex);
            prg->attach_shader(fs);
            prg->attach_shader(gs);
            prg->attach_shader(vs);
            prg->link();
        }
        catch (gle::compilation_failed_exception_t const& exc)
        {
            std::cerr << exc.name() << "\n" << exc.reason() << "\n";
        }

        clean_prg = gle::default_engine()->programs()->create_program("rasterizer_clean");
        try
        {
            gle::shader_ptr fs = gle::default_engine()->programs()->load_shader(
                "shaders/rasterizer_clean_fs.glsl",
                gle::ST_fragment);
            gle::shader_ptr vs = gle::default_engine()->programs()->load_shader(
                "shaders/rasterizer_clean_vs.glsl",
                gle::ST_vertex);
            clean_prg->attach_shader(fs);
            clean_prg->attach_shader(vs);
            clean_prg->link();
        }
        catch (gle::compilation_failed_exception_t const& exc)
        {
            std::cerr << exc.name() << "\n" << exc.reason() << "\n";
        }
    }

    void setup_vao()
    {
        vao = gle::default_engine()->vaos()->create_vertex_array();
        vtx_binding = vao->reserve_binding();

        static gle::vertex_format_t const pos_fmt(gle::float_vertex_format(2, GL_FLOAT, 0, false));
        static gle::vertex_format_t const dist_fmt(gle::float_vertex_format(1, GL_FLOAT, sizeof(float) * 2, false));

        vao->add_vertex_attrib(prg->input_var("in_pos"), pos_fmt, vtx_binding);
        vao->add_vertex_attrib(prg->input_var("in_dist"), dist_fmt, vtx_binding);
    }

    void setup_fbo(int width, int height)
    {
        fbo = gle::default_engine()->fbos()->create_framebuffer();

        gle::texture_ptr tex0 = gle::default_engine()->textures()->create_texture(gle::TT_2d);
        tex0->set_mag_filter(gle::TMAGF_nearest);
        tex0->set_min_filter(gle::TMINF_nearest);
        tex0->image_2d(0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);

        fbo->color_attachment(0)->attach_texture(tex0, 0);

        std::vector<int> buffers(1);

        buffers[0] = 0;
        fbo->set_draw_buffers(buffers);
    }
};

rasterizer_t::rasterizer_t(int width, int height)
    : impl_(new impl_t(width, height))
{}

rasterizer_t::~rasterizer_t() {}


void rasterizer_t::begin_rasterization(size_t num_segments, gle::image_binding_t binding)
{
    int pow2 = 1;
    while (num_segments > pow2) pow2 <<= 1;

    impl_->lines_data->image_1d(0, GL_RGBA32UI, pow2, 0,
        GL_RGBA_INTEGER, GL_UNSIGNED_INT, NULL);

    impl_->prg->var("img_lines_data")->set(binding);
    gle::default_engine()->textures()->bind_image(binding, impl_->lines_data, 0, gle::ITA_write_only, GL_RGBA32UI);

    old_vp_ = gle::default_engine()->viewport();
    gle::default_engine()->set_viewport(
                gle::viewport_t(0, 0, tex_rastr()->width(), tex_rastr()->height()));

    gle::default_engine()->fbos()->set_draw_framebuffer(impl_->fbo);

    gle::default_engine()->programs()->use(impl_->clean_prg);
    quad01::draw(impl_->clean_prg->input_var("in_pos"));

    gle::default_engine()->programs()->use(impl_->prg);
    gle::default_engine()->vaos()->set_current(impl_->vao);

    gle::default_engine()->disable(gle::ES_depth_test);

}

void rasterizer_t::rasterize(newline_data_t const& line, int offset)
{
    impl_->prg->var("color")->set(line.color());
    impl_->prg->var("offset")->set(offset);
    impl_->vao->bind_buffer(impl_->vtx_binding, line.segments(), 0, sizeof(newline_vertex_t));

    gle::default_engine()->draw_arrays(gle::DM_line_strip, 0, line.count());

    impl_->vao->unbind_buffer(impl_->vtx_binding);
}

void rasterizer_t::end_rasterization()
{
    gle::default_engine()->enable(gle::ES_depth_test);

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->vaos()->reset_current();

    gle::default_engine()->fbos()->set_draw_framebuffer_default();
    gle::default_engine()->set_viewport(old_vp_);
}

gle::texture_ptr rasterizer_t::tex_rastr() const
{
    return impl_->fbo->color_attachment(0)->texture();
}

gle::texture_ptr rasterizer_t::tex_data() const
{
    return impl_->lines_data;
}

}
