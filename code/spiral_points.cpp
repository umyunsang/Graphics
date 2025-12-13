// ----------------------------
// 학습 주제: 나선형 점 그리기 (Spiral Points)
// 핵심 개념:
// 1. 원 그리기 코드에 Z축 이동을 추가
//    x = r * cos(theta)
//    y = r * sin(theta)
//    z = z + step
// 2. 각도가 증가함에 따라 z값도 일정하게 증가/감소하여 나선 형태 생성
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

void RenderScene(void) {
    GLfloat x, y, z, angle;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix(); // 현재 행렬 저장

    // 시각적 효과를 위해 회전 (나선이 잘 보이도록)
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glRotatef(45, 0.0f, 1.0f, 0.0f);

    glPointSize(2.0f);
    glBegin(GL_POINTS);

    z = -50.0f; // 시작 깊이

    // 3바퀴(6 PI) 회전
    for(angle = 0.0f; angle <= (2.0f * 3.14f) * 3.0f; angle += 0.1f) {
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        glVertex3f(x, y, z);

        // z값을 조금씩 증가시켜 나선형 궤적 생성
        z += 0.5f; 
    }

    glEnd();
    glPopMatrix(); // 행렬 복원
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
    glutCreateWindow("Spiral Points (나선형 점 그리기)");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
