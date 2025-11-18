#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>
#include <random>

/*
1.
점들 대신에 x-y평면에 있는 속이 빈 작은 정사각형들로 이루어진 3바퀴 회전하는 나선 모양 그리기.
단, 각 정사각형의 색상은 그 형태를 확인할 수 있는 랜덤색으로 적용.
나선 중심은 원점 근처에 있어야 하고 반지름 길이는 50으로 설정.

2.
x축(빨간색), y축(초록색), z축(파란색)을 원점에서 부터 + 방향으로 길이가 100인 화살표로 축 그리기.

같은 뷰에 1번과 2번을 동시에 그리기.
*/



void RenderScene(void) {
    GLfloat x, y, z, angle;
    GLfloat r, g, b;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glRotatef(45, 0.0f, 1.0f, 0.0f);

    // 1. 나선형 정사각형 그리기 (3바퀴)
    z = -50.0f;
    for(angle = 0.0f; angle <= (2.0f * 3.14f) * 3.0f; angle += 0.1f) {
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        // 랜덤 색상
        r = rand() % 100 / 99.0f;
        g = rand() % 100 / 99.0f;
        b = rand() % 100 / 99.0f;

        glColor3f(r, g, b);

        glBegin(GL_LINE_LOOP);
        glVertex3f(x - squareSize, y - squareSize, z);
        glVertex3f(x + squareSize, y - squareSize, z);
        glVertex3f(x + squareSize, y + squareSize, z);
        glVertex3f(x - squareSize, y + squareSize, z);
        glEnd();

        z += 0.5f;
    }


    // X축 (빨간색)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(100.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();

    // Y축 (초록색)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f, 100.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // Z축 (파란색)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 100.0f);
    glPopMatrix();

    glPopMatrix();
    glFlush();
}
void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 100;
    GLfloat aspectRatio;

    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -200, 200);
    } else {
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -200, 200);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("11.05퀴즈");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();

    return 0;
}
