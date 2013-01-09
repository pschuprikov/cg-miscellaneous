#include <glengine.h>

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glut.h>
#include <GL/glext.h>

gle::i_engine * eng;

GLenum err;

int width;
int height;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    width = w;
    height = h;
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

gle::program_ptr load_program()
{
    gle::program_ptr program;
    try
    {
        program = eng->programs()->create_program("test");
        gle::shader_ptr vs = eng->programs()->load_shader(
                    "/home/pasha/repos/cg-miscellaneous/glengine_testing/vs.glsl", gle::ST_vertex);
        gle::shader_ptr fs = eng->programs()->load_shader(
                    "/home/pasha/repos/cg-miscellaneous/glengine_testing/fs.glsl", gle::ST_fragment);
        gle::shader_ptr gs = eng->programs()->load_shader(
                    "/home/pasha/repos/cg-miscellaneous/glengine_testing/gs.glsl", gle::ST_geometry);
        program->attach_shader(vs);
        program->attach_shader(fs);
        program->attach_shader(gs);
        program->link();
    }
    catch (gle::compilation_failed_exception_t const& cfe)
    {
        std::cerr << cfe.what();

        std::cerr << "reason:\n";
        std::cerr << cfe.reason();
    }

    return program;
}

gle::program_ptr load_draw_texture_program()
{
    gle::program_ptr program;
    try
    {
        program = eng->programs()->create_program("draw tex");
        gle::shader_ptr vs = eng->programs()->load_shader(
                    "/home/pasha/repos/cg-miscellaneous/glengine_testing/tex_draw_vs.glsl", gle::ST_vertex);
        gle::shader_ptr fs = eng->programs()->load_shader(
                    "/home/pasha/repos/cg-miscellaneous/glengine_testing/tex_draw_fs.glsl", gle::ST_fragment);
        program->attach_shader(vs);
        program->attach_shader(fs);
        program->link();
    }
    catch (gle::compilation_failed_exception_t const& cfe)
    {
        std::cerr << cfe.what();

        std::cerr << "reason:\n";
        std::cerr << cfe.reason();
    }

    return program;
}

void handleKeyboard(unsigned char btn, int x, int y)
{
    exit(0);
}

gle::texture_ptr load_texture()
{
    static float tex_colors_data[] = {
        1.0f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f
    };
    assert(eng->get_error() == GL_NO_ERROR);
    gle::texture_ptr tex_color = eng->textures()->create_texture(gle::TT_1d);
    assert(eng->get_error() == GL_NO_ERROR);
    tex_color->image_1d(0, GL_RGBA32F, 3, 0, GL_RGB, GL_FLOAT, tex_colors_data);
    tex_color->set_mag_filter(gle::TMAGF_nearest);
    tex_color->set_min_filter(gle::TMINF_nearest);
    assert(eng->get_error() == GL_NO_ERROR);
    return tex_color;
}

gle::framebuffer_ptr create_framebuffer(int width, int height)
{
    gle::framebuffer_ptr fb = eng->fbos()->create_framebuffer();

    gle::texture_ptr fb_color = eng->textures()->create_texture(gle::TT_2d);
    gle::texture_ptr fb_depth = eng->textures()->create_texture(gle::TT_rectangle);
    fb_color->set_mag_filter(gle::TMAGF_nearest);
    fb_color->set_min_filter(gle::TMINF_nearest);

    fb_color->image_2d(0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    fb_depth->image_2d(0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

    assert(!eng->get_error());

    fb->color_attachment(0)->attach_texture(fb_color, 0);
    fb->depth_attachment()->attach_texture(fb_depth, 0);
    std::vector<int> draw_buffers;
    draw_buffers.push_back(0);
    fb->set_draw_buffers(draw_buffers);

    return fb;
}

void draw_fullscreen_tex(gle::texture_ptr tex)
{
    static const float vtx_data[] = {
        -1.0f, -1.0f, 0.f, 0.f,
        1.0f, -1.0f, 1.f, 0.f,
        -1.0f, 1.0f, 0.f, 1.f,
        1.0f, 1.0f, 1.f, 1.f
    };


    static gle::program_ptr tex_draw_mat;
    static gle::vertex_array_ptr vao;
    static gle::shader_variable_ptr tex_uniform;
    static gle::shader_input_variable_ptr pos;
    static gle::shader_input_variable_ptr st;

    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;

        tex_draw_mat = load_draw_texture_program();
        vao = eng->vaos()->create_vertex_array();

        gle::buffer_ptr vtx_buf = eng->buffers()->create_buffer();
        vtx_buf->buffer_data(gle::BU_static_draw, sizeof(vtx_data), vtx_data);
        pos = tex_draw_mat->input_var("in_pos");
        st = tex_draw_mat->input_var("in_st");
        tex_uniform = tex_draw_mat->var("tex_draw");

        gle::vertex_attrib_binding_t vtx_data_binding = vao->bind_buffer(vtx_buf, 0, sizeof(float) * 4);
        gle::vertex_format_ptr pos_fmt(new gle::float_vertex_format_entry(2, GL_FLOAT, 0, false));
        gle::vertex_format_ptr st_fmt(new gle::float_vertex_format_entry(2, GL_FLOAT, sizeof(float) * 2, false));
        vao->add_vertex_attrib(pos, pos_fmt, vtx_data_binding);
        vao->add_vertex_attrib(st, st_fmt, vtx_data_binding);
    }

    gle::texture_binding_t tex_binding = eng->textures()->bind_texture(tex);
    tex_uniform->set(tex_binding);

    eng->vaos()->set_current(vao);

    eng->programs()->use(tex_draw_mat);
    eng->vaos()->draw_arrays(gle::DM_triangle_strip, 0, 4);

    eng->textures()->unbind_texture(tex_binding);
}

void renderScene(void) {

    glDisable(GL_DEPTH_TEST);

    static int frame = 0;
    frame++;

    static gle::time_elapsed_query_ptr prq = eng->queries()->create_time_elapsed_query();
    static gle::primitives_generated_query_ptr prg = eng->queries()->create_primitives_generated_query();
    static gle::samples_passed_query_ptr spq = eng->queries()->create_samples_passed_query();

    static bool unanswered = false;

    static gle::program_ptr program = load_program();
    static gle::shader_block_ptr colors = program->block("colors");

    static gle::mapped_block_adaptor_ptr adaptor = colors->mapped_adapter();
    static gle::shader_variable_ptr cur_sample = adaptor->var("cur_sample");
    static gle::shader_array_ptr samples_passed = adaptor->array("samples[0]");
    static gle::shader_input_variable_ptr pos = program->input_var("in_pos");

    static gle::buffer_ptr colors_buf = eng->buffers()->create_buffer();
    static std::vector<char> colors_cpu_buf(colors->data_size() + samples_passed->stride());
    adaptor->set_pointer(&colors_cpu_buf[0]);


    cur_sample->set(0);

    if (spq->is_result_ready())
    {
        samples_passed->get(1)->set(std::max((int)spq->samples_passed(), 1));
    }

    colors_buf->buffer_data(gle::BU_static_draw, colors_cpu_buf.size(), &colors_cpu_buf[0]);

    static gle::i_indexed_buffer_target_t * colors_tgt = eng->buffers()->buffer_target(gle::BITT_shader_storage, 0);

    colors_tgt->bind_buffer(colors_buf);

    colors->set_binding(colors_tgt->idx());

    static float vpos[] = {
        -1.0f, -1.0f, 1.0f,
        0.0f,  1.0f, 1.0f,
        1.0f,  0.0f, 1.0f
    };

    static gle::texture_ptr tex_color = load_texture();

    static gle::texture_binding_t tex_color_binding = eng->textures()->bind_texture(tex_color);
    static gle::shader_variable_ptr tex_color_var = program->var("tex_colors");
    tex_color_var->set(tex_color_binding);


    static gle::buffer_ptr pos_buf = eng->buffers()->create_buffer();
    pos_buf->buffer_data(gle::BU_static_draw, sizeof(vpos), vpos);
    static gle::vertex_array_ptr vao = eng->vaos()->create_vertex_array();
    static gle::vertex_format_ptr fmt(new gle::float_vertex_format_entry(3, GL_FLOAT, 0, false));
    static gle::vertex_attrib_binding_t pos_binding = vao->bind_buffer(pos_buf, 0, sizeof(float) * 3);
    vao->add_vertex_attrib(pos, fmt, pos_binding);

    static gle::framebuffer_ptr fbo = create_framebuffer(1000, 1000);

    // Clear Color and Depth Buffers
    eng->clear(gle::BPB_color);

    // Set the camera
    glm::mat4 mv = glm::lookAt(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    mv = glm::rotate(mv, angle, glm::vec3(0, 0, 1));

    eng->fbos()->set_draw_framebuffer(fbo);

    glViewport(0, 0, 1000, 1000);

    if (!unanswered)
    {
        prq->begin_query();
        prg->begin_query();
        spq->begin_query();
    }

    eng->programs()->use(program);

    eng->clear_color(glm::vec4(1, 1, 0, 0));
    eng->clear(gle::BPB_color);

    static glm::mat4 proj = glm::ortho<float>(-5, 5, -5, 5, 0, 10);

    glm::mat4 mvp = proj * mv;
    program->var("mvp")->set(mvp);

    eng->vaos()->set_current(vao);
    eng->vaos()->draw_arrays(gle::DM_triangles, 0, 3);


    if (!unanswered)
    {
        prq->end_query();
        prg->end_query();
        spq->end_query();
        unanswered = true;
    }

    std::cerr << prq->time_elapsed_ns() * 1.e-6 << "ms; " << prg->primitives_generated()
              << " gen primitives; " << spq->samples_passed() << " samples_passed" << std::endl;
    unanswered = false;


    eng->fbos()->set_draw_framebuffer_default();

    glViewport(0, 0, width, height);

    static const float dummy_tex_data[] =
    {
        0.f, 0.f,
        1.f, 0.f,
        0.f, 1.f,
        1.f, 1.f
    };

    static gle::texture_ptr dummy_tex;

    if (!dummy_tex)
    {
        dummy_tex = eng->textures()->create_texture(gle::TT_2d);
        dummy_tex->set_min_filter(gle::TMINF_linear);
        dummy_tex->image_2d(0, GL_RGBA32F, 2, 2, 0, GL_RG, GL_FLOAT, dummy_tex_data);
    }

    draw_fullscreen_tex(fbo->color_attachment(0)->texture());

    assert(eng->get_error() == GL_NO_ERROR);

    angle += 0.1f;

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    eng = gle::default_engine();

    // register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeyboard);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
