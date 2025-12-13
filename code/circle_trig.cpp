// ----------------------------
// 학습 주제: 삼각함수를 이용한 원 그리기 (Circle using Trigonometry)
// 핵심 개념:
// 1. 원의 매개변수 방정식:
//    x = r * cos(theta)
//    y = r * sin(theta)
// 2. 반복문(for)을 사용하여 각도(theta)를 증가시키며 점을 찍음
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>    // sin, cos 사용을 위해 필수

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    
    // 0도부터 360도(2*PI)까지 0.5 라디안 간격으로 점을 찍음
    // PI = 3.141592...
    for (float alpha = 0; alpha < 2 * 3.14f; alpha += 0.1f) {
        float radius = 50.0f; // 반지름 50
        
        float x = radius * cos(alpha);
        float y = radius * sin(alpha);
        float z = 0.0f; 
        
        glVertex3f(x, y, z);
    }
    glEnd();

    glFlush();
}

void SetupRc(void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
    glutCreateWindow("Draw Circle with Trigonometry");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
