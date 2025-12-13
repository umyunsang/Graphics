// ----------------------------
// 학습 주제: 직선 그리기 (점들의 집합)
// 핵심 개념:
// 1. 선형 보간 (Linear Interpolation)
//    P(t) = (1-t)*Start + t*End  (0 <= t <= 1)
// 2. 반복문을 통해 t값을 0에서 1로 증가시키며 중간 점들을 계산하여 찍음
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
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    
    // 시작점(0,0,0) ~ 끝점(50,50,50) 사이를 20등분하여 점을 찍음
    // 결과적으로 점선 형태의 직선이 그려짐
    for (int i = 0; i <= 20; ++i) {
        float t = i / 20.0f; // t는 0.0 ~ 1.0 사이의 값
        
        // P = Start + t * (End - Start) 공식 적용 (Start=0 이므로 간단화됨)
        float x = 50.0f * t;
        float y = 50.0f * t;
        float z = 50.0f * t;
        
        glVertex3f(x, y, z);
    }
    glEnd();

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
    glutCreateWindow("Draw Line with Points");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
