// ----------------------------
// 학습 주제: gluLookAt 값에 따른 가시성 판정 (시험 핵심)
// ★★★ 제일 중요 (시험 출제) ★★★
//
// 핵심 개념:
// 1. 카메라 위치와 방향 (gluLookAt)
// 2. 투영 범위 (glOrtho)와 Z축 반전 (near > far)
// 3. 깊이 테스트 (Depth Test) 및 후면 제거 (Cull Face) 영향
//
// [문제 상황]
// - 원 A (Blue, 지름 40): z = 10 위치
// - 원 B (Red,  지름 20): z = 20 위치
// - glOrtho(-100, 100, -100, 100, -100, 100) -> near < far (정상)
// - 깊이 테스트 ON, 후면 제거 OFF
//
// [시나리오 1: gluLookAt(0,0,0,  0,0,-1,  0,1,0)]
// - 카메라: 원점(0,0,0)에서 -Z 방향을 바라봄
// - 원 A(z=10), 원 B(z=20) 모두 카메라 뒤쪽(+Z)에 있음?
//   아니라, OpenGL 좌표계는 오른손 좌표계이므로
//   -Z를 볼 때 +Z에 있는 물체는 "뒤"에 있음 -> 안 보여야 정상.
//   하지만 glOrtho가 -100 ~ 100을 포함하므로 투영 영역 안에 들어옴.
//   Z=10, 20은 카메라보다 "앞"이 아니라 "뒤"지만, Ortho 박스 안에는 있음.
//   만약 카메라가 -Z를 본다면, +Z에 있는 물체는 카메라 뒤통수 쪽에 있는 것.
//   그러나 Ortho 투영은 "상자"를 정의하므로 박스 안에 있으면 그림.
//   단, "보이는가"는 깊이 테스트 결과에 따름.
//
// [시나리오 2: gluLookAt(0,0,0,  0,0,1,   0,1,0)]
// - 카메라: 원점(0,0,0)에서 +Z 방향을 바라봄
// - 원 A(z=10)가 원 B(z=20)보다 카메라에 가까움
// - 원 A(큰 원)가 원 B(작은 원)를 가림 -> Blue만 보임
//
// [함정: near > far 인 경우]
// - 예: glOrtho(..., 100, -100)
// - Z축의 깊이 값이 반전됨. 멀리 있는 게 depth 값이 작아질 수 있음.
// - 가시성 판정이 뒤집힐 수 있음에 유의.
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
    // 깊이 버퍼 클리어 필수
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);  // 후면 제거 OFF (양면 모두 그림)
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 ON

    GLfloat angle, x, y;

    // 1. Red 원 (z=20, 지름 20)
    // - 카메라(원점)에서 거리가 20
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f);    // 빨강
        glVertex3f(0.0f, 0.0f, 20.0f);  // 중심 z=20

        for (angle = 0.0f; angle <= 2.0f * PI + 0.01f; angle += (2.0f * PI) / 16.0f) {
            x = 10.0f * cos(angle);     // 반지름 10
            y = 10.0f * sin(angle);
            glVertex3f(x, y, 20.0f);
        }
    glEnd();

    // 2. Blue 원 (z=10, 지름 40)
    // - 카메라(원점)에서 거리가 10 (더 가까움)
    // - 더 크기 때문에 뒤에 있는 Red 원을 가릴 가능성 있음
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);    // 파랑
        glVertex3f(0.0f, 0.0f, 10.0f);  // 중심 z=10

        for (angle = 0.0f; angle <= 2.0f * PI + 0.01f; angle += (2.0f * PI) / 16.0f) {
            x = 20.0f * cos(angle);     // 반지름 20
            y = 20.0f * sin(angle);
            glVertex3f(x, y, 10.0f);
        }
    glEnd();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ★ glOrtho 설정 (투영 박스)
    // near=-100, far=100 (정상)
    glOrtho(-100, 100, -100, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ★ 카메라 설정 (시험 포인트)
    // Case 1: -Z 방향 보기 (일반적) -> eye(0,0,0), center(0,0,-1)
    // Case 2: +Z 방향 보기 (물체 쪽) -> eye(0,0,0), center(0,0,1)
    
    // 현재 설정: +Z 방향을 바라봄 (물체들이 z=10, 20에 있으므로 정면으로 봄)
    gluLookAt(0.0f, 0.0f, 0.0f,    // Eye
              0.0f, 0.0f, 1.0f,    // Center (Look at +Z)
              0.0f, 1.0f, 0.0f);   // Up
              
    // 결과 예측:
    // 카메라가 +Z를 봄. z=10(Blue)이 z=20(Red)보다 앞에 있음.
    // Blue가 Red를 가림.
    // Blue 원만 보여야 함.
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Exam Question: Camera & Depth");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    std::cout << "★ 시험 문제 시뮬레이션 ★" << std::endl;
    std::cout << "Camera looking at +Z (0,0,1)" << std::endl;
    std::cout << "Blue Circle (z=10, r=20) vs Red Circle (z=20, r=10)" << std::endl;
    std::cout << "Result: Blue covers Red (Blue only visible)" << std::endl;

    glutMainLoop();
    return 0;
}