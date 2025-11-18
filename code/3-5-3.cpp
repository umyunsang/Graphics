#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>


void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 첫 번째 삼각형 - 빨간색 (채우기)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 50.0f, 0.0f);    // 위 (반시계 방향으로 정의)
        glVertex3f(-40.0f, -30.0f, 0.0f); // 왼쪽 아래
        glVertex3f(40.0f, -30.0f, 0.0f);  // 오른쪽 아래
    glEnd();

    // 두 번째 삼각형 - 초록색 (와이어프레임)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-80.0f, 50.0f, 0.0f);   // 위
        glVertex3f(-80.0f, 0.0f, 0.0f);    // 왼쪽 아래
        glVertex3f(-40.0f, 0.0f, 0.0f);    // 오른쪽 아래
    glEnd();

    // 세 번째 삼각형 - 파란색 (채우기로 다시 변경)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(80.0f, 50.0f, 0.0f);    // 위
        glVertex3f(40.0f, 0.0f, 0.0f);     // 왼쪽 아래
        glVertex3f(80.0f, 0.0f, 0.0f);     // 오른쪽 아래
    glEnd();

    glFlush();
}

void SetupRc(void)
{
    std::cout << "OpenGL Basic Triangle Example" << std::endl;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 흰색 배경
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

    glutCreateWindow("Basic Triangle Example");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutDisplayFunc(RenderScene);

    glutReshapeFunc(ChangeSize);

    glutMainLoop();

    return 0;
}