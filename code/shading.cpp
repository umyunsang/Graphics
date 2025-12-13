// ----------------------------
// 학습 주제: 쉐이딩 모델 (Flat vs Smooth)
// 핵심 개념:
// 1. glShadeModel(GL_FLAT):
//    - 면의 한 가지 색상(보통 마지막 정점의 색)으로 전체를 칠함.
//    - 각진 느낌.
// 2. glShadeModel(GL_SMOOTH) - 기본값:
//    - 정점마다 지정된 색상을 부드럽게 보간(Interpolation).
//    - 그라데이션 효과 발생.
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 삼각형 그리기 (각 정점마다 다른 색상 지정)
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // V1: 빨강
        glVertex2f(0.0f, 0.0f);
        
        glColor3f(0.0f, 1.0f, 0.0f); // V2: 초록
        glVertex2f(50.0f, 0.0f);
        
        glColor3f(0.0f, 0.0f, 1.0f); // V3: 파랑
        glVertex2f(50.0f, 50.0f);
    glEnd();

    glFlush();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // ★ 쉐이딩 모델 설정 ★
    // GL_FLAT: 보간 없음 (마지막 정점인 파란색으로 칠해질 가능성 높음)
    // GL_SMOOTH: 부드러운 그라데이션 (빨강-초록-파랑 섞임)
    glShadeModel(GL_FLAT); 
    // glShadeModel(GL_SMOOTH); 
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 100;
    GLfloat aspectRatio;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100, 100);
    else        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Shading Model (Flat vs Smooth)");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    SetupRC(); // 초기화 함수에서 glShadeModel 설정

    std::cout << "GL_FLAT 모드: 단색 렌더링" << std::endl;
    std::cout << "GL_SMOOTH 모드: 그라데이션 렌더링" << std::endl;

    glutMainLoop();
    return 0;
}