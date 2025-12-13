// ----------------------------
// 학습 주제: 타이머 함수를 이용한 자동 배경색 변경
// 핵심 개념:
// 1. glutTimerFunc(msecs, func, value): 일정 시간(ms) 후 함수 호출
// 2. 재귀적 호출: Timer 함수 내에서 다시 TimerFunc를 호출하여 반복 실행
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

int colorIndex = 0; // 0: Red, 1: Green, 2: Blue

// 타이머 콜백 함수
void TimerFunction(int value)
{
    // 색상 인덱스 변경
    colorIndex = (colorIndex + 1) % 3;

    // 화면 갱신 요청
    glutPostRedisplay();

    // 1000ms(1초) 후에 다시 이 함수를 호출 (반복)
    glutTimerFunc(1000, TimerFunction, 1);
}

void RenderScene(void)
{
    // colorIndex에 따라 배경색 설정
    switch (colorIndex)
    {
    case 0: glClearColor(1.0f, 0.0f, 0.0f, 1.0f); break; // 빨강
    case 1: glClearColor(0.0f, 1.0f, 0.0f, 1.0f); break; // 초록
    case 2: glClearColor(0.0f, 0.0f, 1.0f, 1.0f); break; // 파랑
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void SetupRC()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) glOrtho(-100.0, 100.0, -100.0 * h / w, 100.0 * h / w, -100.0, 100.0);
    else        glOrtho(-100.0 * w / h, 100.0 * w / h, -100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Timer Background Change");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    // 프로그램 시작 1초 후 첫 타이머 실행
    glutTimerFunc(1000, TimerFunction, 1);

    glutMainLoop();
    return 0;
}