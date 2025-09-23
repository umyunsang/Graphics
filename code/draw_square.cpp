#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    std::cout << "RenderScene" << std::endl;

    glViewport(0, 0, 500, 500);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glOrtho(0, 480, 0, 480, -1, 1);
    // 사각형 좌표는 고정: glRectf(0, 240, 320, 0)
    glRectf(0, 240, 320, 0);

    glFlush();
}

void SetupRc(void)
{
    std::cout << "SetupRc" << std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Fixed Square");

    SetupRc();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
    return 0;
}