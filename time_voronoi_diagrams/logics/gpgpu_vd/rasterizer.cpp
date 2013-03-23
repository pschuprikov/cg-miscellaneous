#include "rasterizer.h"

namespace tvd
{

struct rasterizer_t::impl_t
{
    gle::vertex_attrib_binding_t vtx_binding;
    int out_location;
    int tmp_location;

    gle::program_ptr prg;
    gle::vertex_array_ptr vao;
    gle::framebuffer_ptr fbo;


    impl_t(int width, int height)
    {
        load_program();
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
        tex0->image_2d(0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, NULL);

        gle::texture_ptr tex_tmp = gle::default_engine()->textures()->create_texture(gle::TT_2d);
        tex_tmp->set_mag_filter(gle::TMAGF_nearest);
        tex_tmp->set_min_filter(gle::TMINF_nearest);
        tex_tmp->image_2d(0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, NULL);

        out_location = 0;
        tmp_location = 1;

        fbo->color_attachment(out_location)->attach_texture(tex0, 0);
        fbo->color_attachment(tmp_location)->attach_texture(tex_tmp, 0);


        std::vector<int> buffers(1);

        buffers.front() = out_location;
        fbo->set_draw_buffers(buffers);

        fbo->set_read_buffer(tmp_location);
    }

public:
    void swap_buffers()
    {
        static std::vector<int> buffers(1);

        std::swap(out_location, tmp_location);

        buffers.front() = out_location;
        fbo->set_draw_buffers(buffers);

        fbo->set_read_buffer(tmp_location);
    }
};

rasterizer_t::rasterizer_t(int width, int height)
    : impl_(new impl_t(width, height))
{}

rasterizer_t::~rasterizer_t() {}


void rasterizer_t::begin_rasterization()
{
    old_vp_ = gle::default_engine()->viewport();
    gle::default_engine()->set_viewport(gle::viewport_t(0, 0, tex()->width(), tex()->height()));

    cleaner_.clean_tex(tex(), glm::uvec4(0, 0, 0, 0));

    gle::default_engine()->vaos()->set_current(impl_->vao);
    gle::default_engine()->fbos()->set_draw_framebuffer(impl_->fbo);
    gle::default_engine()->programs()->use(impl_->prg);


    gle::default_engine()->disable(gle::ES_depth_test);
}

void rasterizer_t::rasterize(newline_data_t const& line)
{
    impl_->prg->var("color")->set(line.color());
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
    impl_->swap_buffers();

    blit_tex();

    gle::default_engine()->set_viewport(old_vp_);
}

void rasterizer_t::blit_tex()
{
    gle::default_engine()->fbos()->set_draw_framebuffer(impl_->fbo);
    gle::default_engine()->fbos()->set_read_framebuffer(impl_->fbo);

    int width = tex()->width();
    int height = tex()->height();

    gle::default_engine()->blit_framebuffer(0, 0, width, height, 0, 0, width, height,
                                            gle::BPB_color, gle::FF_nearest);
    gle::default_engine()->fbos()->set_draw_framebuffer_default();
    gle::default_engine()->fbos()->set_read_framebuffer_default();
}

gle::texture_ptr rasterizer_t::tex() const
{
    return impl_->fbo->color_attachment(impl_->out_location)->texture();
}

}
