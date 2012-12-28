#include <glengine.h>
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

void renderScene(void) {

    static gle::time_elapsed_query_ptr prq = eng->queries()->create_time_elapsed_query();
    static gle::primitives_generated_query_ptr prg = eng->queries()->create_primitives_generated_query();
    static gle::samples_passed_query_ptr spq = eng->queries()->create_samples_passed_query();
    static gle::buffer_ptr vtx_buf = eng->buffers()->create_buffer();
    static gle::buffer_ptr ind_buf = eng->buffers()->create_buffer();

    float data[] = { -2.0f, -2.0f, 0.0f,
                      2.0f,  0.0f, 0.0f,
                      0.0f,  2.0f, 0.0f };
    GLuint indicies[] = { 0, 1, 2 };
    vtx_buf->buffer_data(gle::BU_static_draw, sizeof(data), data);
    ind_buf->buffer_data(gle::BU_static_draw, sizeof(indicies), indicies);

    eng->buffers()->buffer_target(gle::BTT_array)->bind_buffer(vtx_buf);
    eng->buffers()->buffer_target(gle::BTT_element_array)->bind_buffer(ind_buf);

    static bool unanswered = false;

    if (!unanswered)
    {
        prq->begin_query();
        prg->begin_query();
        spq->begin_query();
    }
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(	0.0f, 0.0f, 10.0f,
                0.0f, 0.0f,  0.0f,
                0.0f, 1.0f,  0.0f);

    for (int i = 0; i < 1000; i++)
    {
        double mult = i / 1000.;

        glRotatef(angle + M_PI_2 * mult, 0.0f, 1.0f, 0.0f);

        mult = rand() / (double) RAND_MAX;
        glColor3f(1 - mult * 0.5, mult, mult * 0.5);

        GL_VERTEX_ARRAY

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    angle+=0.1f;

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
