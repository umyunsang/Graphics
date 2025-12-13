// ----------------------------
// 학습 주제: 점선 그리기 (Factor 변경 - 간격 조절)
// 핵심 개념:
// 1. glLineStipple(factor, pattern)
// 2. factor: 패턴의 각 비트를 몇 번 반복할지 결정
//    factor=1: 1010... -> 1픽셀 선, 1픽셀 공백
//    factor=2: 11001100... -> 2픽셀 선, 2픽셀 공백
//    factor가 커질수록 점선의 간격(과 길이)이 늘어남
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    GLfloat y;
    GLint factor = 1;           // 초기 factor 1
    GLushort pattern = 0x5555;  // 0101010101010101 (기본 점선 패턴)

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();

    glEnable(GL_LINE_STIPPLE);

    for(y = -90.0f; y <= 90.0f; y += 20.0f) {
        
        glLineStipple(factor, pattern);
        
        glBegin(GL_LINES);
        glVertex3f(-80.0f, y, 0.0f);
        glVertex3f(80.0f, y, 0.0f);
        glEnd();
        
        // factor를 증가시켜 점선이 점점 굵어지고 간격이 넓어지게 함
        factor++; 
    }

    glDisable(GL_LINE_STIPPLE);

    glPopMatrix();
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
    glutCreateWindow("Line Stipple Factor");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}