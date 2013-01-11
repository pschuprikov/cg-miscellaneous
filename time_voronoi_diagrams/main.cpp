#include <iostream>
#include "core/core.h"
#include "logics/main_logic.h"

using namespace std;

int main(int argc, char * argv[])
{
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    tvd::core_t::instance()->run(tvd::logic_ptr(new tvd::main_logic_t()), 0, 0, 1000, 1000, "Hello world");

    return 0;
}

