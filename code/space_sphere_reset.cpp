// ----------------------------
// 학습 주제: glLoadIdentity()를 이용한 행렬 초기화 주의점
// 핵심 개념:
// 1. glLoadIdentity()는 현재 선택된 행렬(ModelView)을 단위 행렬로 리셋함.
// 2. 주의: 이전에 적용했던 '카메라 변환'까지 모두 사라짐!
// 3. 카메라 위치가 원점(0,0,0)으로, 바라보는 방향이 -Z로 초기화됨.
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // 1. 카메라 변환 적용
    glTranslatef(0.0f, 0.0f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    // 축 그리기
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    // 2. 첫 번째 구 (카메라 변환 적용됨)
    // 현재 시점: (0,0,-30) 이동 후 회전된 상태
    // 물체 위치: 여기서 Y=10 이동
    glTranslatef(0.0f, 10.0f, 0.0f);
    glutSolidSphere(1.0f, 30, 30);

    // 3. 행렬 초기화 (!!! 주의 !!!)
    // 이제 모든 변환(카메라 포함)이 사라지고 원점(0,0,0) 상태로 돌아감
    glLoadIdentity();

    // 4. 두 번째 구
    // 카메라 위치: (0,0,0)
    // 물체 위치: (10,0,0)
    // 카메라가 원점에 있고 물체는 X=10에 있음.
    // 만약 카메라가 -Z를 본다면, (10,0,0)은 오른쪽에 보일 것임.
    // 하지만 깊이/원근감은 초기화된 카메라 기준이 됨.
    glTranslatef(10.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 30, 30);

    glFlush();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, (GLfloat)w / (GLfloat)h, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Matrix Reset Warning");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}