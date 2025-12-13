// ----------------------------
// 학습 주제: 점 그리기 (Drawing Points)
// 핵심 개념:
// 1. glBegin(GL_POINTS) ~ glEnd(): 점을 그리는 기본 블록
// 2. glVertex3f(x, y, z): 3차원 좌표에 정점(Vertex) 위치 지정
// 3. glPointSize(size): 점의 크기 설정 (기본값 1.0)
//
// 참고: (0,0,0) 점이 안 보일 경우 투영(Projection) 설정 확인 필요.
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색 설정
    glPointSize(8.0f);           // 점의 크기를 8.0으로 확대

    // 점 그리기 시작
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);          // 원점 (0,0,0)
        glVertex3f(50.0f, 50.0f, 50.0f);       // (50,50,50) 위치
    glEnd();
    // 점 그리기 종료

    glFlush();
}

void SetupRc(void)
{
    std::cout << "SetupRc" << std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 배경: 파란색
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 100;
    GLfloat aspectRatio;

    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    // 점이 잘 보이도록 좌표 공간(Orthographic)을 -100 ~ 100으로 설정
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
    glutCreateWindow("Point Drawing (점 그리기)");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
