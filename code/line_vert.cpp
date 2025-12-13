// ----------------------------
// 학습 주제: 세로 선 그리기 (Vertical Lines)
// 핵심 개념:
// 1. GL_LINES: 두 점(Vertex)을 한 쌍으로 하여 선분 그림
// 2. 좌표 계산: x좌표를 변경하고 y좌표를 고정하여 세로선 배치
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    GLfloat Width = 10.0f;
    GLfloat x = 80.0f;

    // 오른쪽에서 왼쪽으로 이동하며 세로선 10개 그리기
    for(int i = 0; i < 10; i++) {
        glLineWidth(Width); // 선 두께 조절

        glBegin(GL_LINES);
        // 세로선: x는 고정, y는 -80 ~ 80
        glVertex3f(x, -80.0f, 0.0f);  
        glVertex3f(x, 80.0f, 0.0f);   
        glEnd();

        Width -= 1.0f;  // 선 두께 1씩 감소
        x -= 18.0f;     // 왼쪽으로 이동
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
    glutCreateWindow("Vertical Lines");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}