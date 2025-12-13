// ----------------------------
// 학습 주제: 점 크기가 증가하는 나선형 그리기
// 핵심 개념:
// 1. 점의 크기를 동적으로 변경: glPointSize(size)
// 2. 색상 변경: glColor3f(r, g, b)
// 3. 루프 내에서 상태(크기, 색상, 위치)를 계속 업데이트하며 그리기
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
    GLfloat pointSize = 1.0f;             // 초기 점 크기
    GLfloat r = 1.0f, g = 0.0f, b = 0.0f; // 초기 색상 (빨강)

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // 나선이 잘 보이도록 시점 회전
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glRotatef(45, 0.0f, 1.0f, 0.0f);

    z = -50.0f; // 시작 깊이

    // 나선 그리기 루프
    for(angle = 0.0f; angle <= (2.0f * 3.14f) * 3.0f; angle += 0.1f) {
        x = 50.0f * cos(angle);
        y = 50.0f * sin(angle);

        // 색상 업데이트 (그라데이션 효과)
        glColor3f(r, g, b);
        r -= 0.01f;
        g += 0.01f;
        b += 0.01f;

        // 점 크기 업데이트 (점점 커짐)
        glPointSize(pointSize);
        pointSize += 0.05f;

        // 점 하나 그리기 (상태가 변경되므로 매번 glBegin/glEnd 필요)
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();

        z += 0.5f; // z값 증가 (나선 진행)
    }
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
    glutCreateWindow("Spiral Points Growing (점 크기 증가 나선)");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 배경 검정

    // 참고: 시스템이 지원하는 점 크기 범위 확인 코드
    GLfloat sizes[2];
    GLfloat step;
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
    std::cout << "Supported Point Size Range: " << sizes[0] << " ~ " << sizes[1] << std::endl;
    std::cout << "Size Step: " << step << std::endl;

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();

    return 0;
}