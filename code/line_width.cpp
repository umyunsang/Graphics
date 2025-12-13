// ----------------------------
// 학습 주제: 선 두께 조절 (Line Width)
// 핵심 개념:
// 1. glLineWidth(width): 선의 두께 설정 (픽셀 단위)
// 2. 루프를 돌며 선 두께를 변경하여 여러 선 그리기
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색

    GLfloat Width = 10.0f; // 초기 선 두께
    GLfloat y = 80.0f;     // 초기 y 위치

    // 위에서 아래로 내려오며 선 10개 그리기
    for(int i = 0; i < 10; i++) {
        glLineWidth(Width); // 선 두께 설정

        glBegin(GL_LINES);
        glVertex3f(-80.0f, y, 0.0f); // 왼쪽 끝
        glVertex3f(80.0f, y, 0.0f);  // 오른쪽 끝
        glEnd();

        Width -= 1.0f; // 두께 감소
        y -= 18.0f;    // 아래로 이동
    }

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
    glutCreateWindow("Line Width Example");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}