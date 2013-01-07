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

void renderScene(void) {

    static gle::time_elapsed_query_ptr prq = eng->queries()->create_time_elapsed_query();
    static gle::primitives_generated_query_ptr prg = eng->queries()->create_primitives_generated_query();
    static gle::samples_passed_query_ptr spq = eng->queries()->create_samples_passed_query();

    static bool unanswered = false;

    static gle::program_ptr program = load_program();

    if (!unanswered)
    {
        prq->begin_query();
        prg->begin_query();
        spq->begin_query();
    }
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glm::mat4 mv(1);
    // Set the camera
    mv = glm::lookAt(glm::vec3(0.f, 0.f, 10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    eng->programs()->use(program);

    for (int i = 0; i < 1; i++)
    {
        double mult = i / 1000.;

        mv = glm::rotate(mv, angle, glm::vec3(0.f, 0.f, 1.f));

        static glm::mat4 proj = glm::ortho<float>(-5, 5, -5, 5);

        glm::mat4 mvp = proj * mv;
        program->var("mvp")->set(mvp);

        mult = rand() / (double) RAND_MAX;
        program->var("color")->set(glm::vec4(1 - mult * 0.5, mult, mult * 0.5, 1));

        glBegin(GL_TRIANGLES);
        glVertex3f(-2.0f, -2.0f, 0.0f);
        glVertex3f(2.0f,  0.0f, 0.0f );
        glVertex3f(0.0f,  2.0f, 0.0f );
        glEnd();
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
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
