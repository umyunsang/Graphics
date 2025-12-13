// ----------------------------
// 학습 주제: 행렬 스택을 이용한 독립적인 물체 배치 (Push/Pop)
// 핵심 개념:
// 1. glPushMatrix(): 현재 모델뷰 행렬 상태를 스택에 저장 (복사본 생성)
// 2. glPopMatrix(): 스택에서 행렬을 꺼내 복원 (저장했던 상태로 되돌아감)
// 3. 활용: 여러 물체를 서로 다른 위치에 그릴 때, 이전 변환의 영향을 받지 않도록 격리
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

    // 1. 카메라 변환 (모든 물체에 공통 적용)
    glTranslatef(0.0f, 0.0f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    // 축 그리기
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // 흰색

    // 2. 첫 번째 구 그리기
    glPushMatrix(); // 현재 상태(카메라 변환만 있는 상태) 저장
        glTranslatef(0.0f, 10.0f, 0.0f); // Y축으로 10 이동
        glutSolidSphere(1.0f, 30, 30);
    glPopMatrix();  // 상태 복원 (Y축 이동 취소됨, 다시 카메라 변환 상태로)

    // 3. 두 번째 구 그리기
    glPushMatrix(); // 현재 상태(카메라 변환만 있는 상태) 저장
        glTranslatef(10.0f, 0.0f, 0.0f); // X축으로 10 이동
        glutSolidSphere(1.0f, 30, 30);
    glPopMatrix();  // 상태 복원

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
    glutCreateWindow("Push/Pop Matrix Example");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}