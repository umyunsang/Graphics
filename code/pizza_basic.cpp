// ----------------------------
// 학습 주제: 피자 원 그리기 (기본)
// 핵심 개념:
// 1. GL_TRIANGLE_FAN 기본 사용법
// 2. 색상 교차 (if count % 2 == 0)
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat angle, x, y;
    int count = 0;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // 중심점

        // 16조각으로 나눔
        for (angle = 0.0f; angle <= 2.0f * PI + 0.01f; angle += (2.0f * PI) / 16.0f) {
            if (count % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f); // 빨강
            else                glColor3f(0.0f, 1.0f, 0.0f); // 초록

            x = 50.0f * cos(angle);
            y = 50.0f * sin(angle);
            glVertex2f(x, y);
            count++;
        }
    glEnd();

    glFlush();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 100;
    GLfloat aspectRatio;

    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 100);
    } else {
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100, 100);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Simple Pizza Circle");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    std::cout << "Basic GL_TRIANGLE_FAN Example" << std::endl;

    glutMainLoop();
    return 0;
}