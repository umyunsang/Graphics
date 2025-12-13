// ----------------------------
// 학습 주제: 정점 5개 사용해서 특정 모양 그리기 (GL_TRIANGLE_STRIP)
// 핵심 개념:
// 1. GL_TRIANGLE_STRIP: 정점들을 연결하여 연속된 삼각형을 생성
//    (V0, V1, V2), (V2, V1, V3), (V2, V3, V4)... 순서로 연결됨
// 2. 정점 순서가 중요함 (반시계/시계 방향에 따라 앞면/뒷면 결정)
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
    
    // 5개의 정점을 사용하여 모양 생성
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.0f, 0.0f);     // V0
        glVertex2f(50.0f, 0.0f);    // V1
        glVertex2f(50.0f, 50.0f);   // V2 -> (V0,V1,V2) 삼각형 1
        glVertex2f(0.0f, 50.0f);    // V3 -> (V2,V1,V3) 삼각형 2
        glVertex2f(50.0f, 100.0f);  // V4 -> (V2,V3,V4) 삼각형 3
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
    glutCreateWindow("Polygon 5 Vertices");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    std::cout << "GL_TRIANGLE_STRIP 예제 (정점 5개)" << std::endl;
    glutMainLoop();
    return 0;
}