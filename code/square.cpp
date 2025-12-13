// ----------------------------
// 학습 주제: 정사각형 그리기 (Square using Triangle Strip)
// 핵심 개념:
// 1. GL_TRIANGLE_STRIP으로 사각형(정사각형) 만들기
// 2. 4개의 정점만 있으면 사각형 1개를 그릴 수 있음 (삼각형 2개 결합)
//    순서: 좌상단 -> 좌하단 -> 우상단 -> 우하단 (일반적인 strip 순서 예시)
//    * 이 코드의 순서는 약간 다를 수 있으나 원리는 동일
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
    
    // 정사각형 그리기
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-50.0f, 50.0f);   // 1. 좌상단
        glVertex2f(-50.0f, -50.0f);  // 2. 좌하단
        glVertex2f(50.0f, 50.0f);    // 3. 우상단 -> (1,2,3) 삼각형
        glVertex2f(50.0f, -50.0f);   // 4. 우하단 -> (3,2,4) 삼각형
    glEnd();

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
    glutCreateWindow("Draw Square");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    std::cout << "GL_TRIANGLE_STRIP으로 정사각형 그리기" << std::endl;
    glutMainLoop();
    return 0;
}