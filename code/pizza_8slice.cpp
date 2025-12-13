// ----------------------------
// 학습 주제: 8조각 피자 원 그리기 + 키보드 제어
// 핵심 개념:
// 1. 키보드 입력(1~8)에 따라 그려지는 조각 개수 제어
// 2. 루프 제어 변수(pieceCount)를 전역으로 두고 Keyboard 콜백에서 수정
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

int pieceCount = 0;  // 현재 그릴 조각 수

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat angle, x, y;
    GLfloat radius = 50.0f;

    // 입력된 개수만큼 반복하여 삼각형 그리기
    for (int i = 0; i < pieceCount; i++) {
        glBegin(GL_TRIANGLES);
            // 색상 교차
            if (i % 2 == 0) glColor3f(0.0f, 1.0f, 0.0f); // 초록
            else            glColor3f(1.0f, 0.0f, 0.0f); // 빨강

            // 중심점
            glVertex2f(0.0f, 0.0f);

            // 원주 위의 두 점 계산 (8등분)
            angle = 2.0f * PI * i / 8.0f;
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex2f(x, y);

            angle = 2.0f * PI * (i + 1) / 8.0f;
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex2f(x, y);
        glEnd();
    }

    glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
    // 숫자 키 1~8 처리
    if (key >= '1' && key <= '8') {
        pieceCount = key - '0';  // 문자를 숫자로 변환
        std::cout << "Drawing " << pieceCount << " slices." << std::endl;
        glutPostRedisplay(); // 화면 갱신
    }
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
    glutCreateWindow("Pizza Slices (Press 1-8)");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);

    std::cout << "Press 1 ~ 8 to draw slices." << std::endl;

    glutMainLoop();
    return 0;
}