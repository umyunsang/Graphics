// ----------------------------
// 학습 주제: 점선 그리기 (패턴 변경)
// 핵심 개념:
// 1. glLineStipple(factor, pattern): 점선 패턴 설정
// 2. pattern (16비트): 1이면 그리고, 0이면 안 그림
//    예) 0x00FF (0000 0000 1111 1111) -> 8픽셀 공백, 8픽셀 선
// 3. glEnable(GL_LINE_STIPPLE)로 활성화 필요
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    GLfloat y;
    GLint factor = 3;            // 확대 배율 고정
    GLushort pattern = 0x00FF;   // 초기 패턴

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();

    glEnable(GL_LINE_STIPPLE); // 점선 기능 켜기

    for(y = -90.0f; y <= 90.0f; y += 20.0f) {
        
        glLineStipple(factor, pattern);
        
        glBegin(GL_LINES);
        glVertex3f(-80.0f, y, 0.0f);
        glVertex3f(80.0f, y, 0.0f); 
        glEnd();
        
        // 패턴 비트를 변경
        // 예: 0x00FF * 16 = 0x0FF0 (패턴이 시프트됨)
        // 비트 연산을 통해 다양한 점선 모양 생성
        pattern = pattern * 16; 
    }

    glDisable(GL_LINE_STIPPLE); // 점선 기능 끄기

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
    glutCreateWindow("Line Stipple Pattern");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}