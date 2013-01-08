#include <glengine.h>

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glut.h>
#include <GL/glext.h>

gle::i_engine * eng;

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

void handleKeyboard(unsigned char btn, int x, int y)
{
    exit(0);
}

void renderScene(void) {

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
    samples_passed->get(1)->set(std::max((int)spq->samples_passed(), 1));
    colors_buf->buffer_data(gle::BU_static_draw, colors_cpu_buf.size(), &colors_cpu_buf[0]);

    static gle::i_indexed_buffer_target_t * colors_tgt = eng->buffers()->buffer_target(gle::BITT_shader_storage, 0);
    colors_tgt->bind_buffer(colors_buf);
    colors->set_binding(colors_tgt->idx());

    static float vpos[] = {
        -1.0f, -1.0f, 1.0f,
        0.0f,  1.0f, 1.0f,
        1.0f,  0.0f, 1.0f
    };
    static gle::buffer_ptr pos_buf = eng->buffers()->create_buffer();
    pos_buf->buffer_data(gle::BU_static_draw, sizeof(vpos), vpos);
    static gle::vertex_array_ptr vao = eng->vaos()->create_vertex_array();
    static gle::vertex_format_ptr fmt(new gle::float_vertex_format_entry(3, GL_FLOAT, 0, false));
    static gle::vertex_attrib_binding_t pos_binding = vao->bind_buffer(pos_buf, 0, sizeof(float) * 3);
    vao->add_vertex_attrib(pos, fmt, pos_binding);

    if (!unanswered)
    {
        prq->begin_query();
        prg->begin_query();
        spq->begin_query();
    }
    // Clear Color and Depth Buffers
    eng->clear(gle::BPB_color | gle::BPB_depth);

    // Set the camera
    glm::mat4 mv = glm::lookAt(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    mv = glm::rotate(mv, angle, glm::vec3(0, 0, 1));


    eng->vaos()->enable_vertex_attrib_array(pos->location());
    eng->programs()->use(program);

    for (int i = 0; i < 1; i++)
    {
        double mult = i / 1000.;

        static glm::mat4 proj = glm::ortho<float>(-5, 5, -5, 5, 0, 10);

        glm::mat4 mvp = proj * mv;
        program->var("mvp")->set(mvp);

        mult = rand() / (double) RAND_MAX;

        eng->vaos()->set_current(vao);
        eng->vaos()->draw_arrays(gle::DM_triangles, 0, 3);
    }

    angle += 0.1f;

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
