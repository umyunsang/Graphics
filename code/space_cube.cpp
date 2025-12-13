// ----------------------------
// 학습 주제: 변환된 공간 + 좌표 축 + 육면체 그리기
// 핵심 개념:
// 1. 모델링 변환 (Model Transformation):
//    - 물체(모델)를 원하는 위치, 크기, 방향으로 배치
//    - 카메라 변환 이후에 적용됨 (코드상으로는 카메라 변환 -> 모델 변환 순서로 작성)
//    - 실제 적용 순서: 모델 정점 -> 모델 변환 -> 카메라 변환 -> 투영
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

    // 1. 카메라 변환 (View)
    glTranslatef(0.0f, 0.0f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    // 2. 축 그리기 (카메라 변환만 적용된 상태)
    glBegin(GL_LINES);
        // X (Red), Y (Green), Z (Blue)
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    // 3. 모델 변환 (Model)
    // 현재 좌표계(카메라 변환이 적용된 상태)에서 Y축으로 10 이동
    glTranslatef(0.0f, 10.0f, 0.0f);

    // 4. 육면체 그리기
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색
    glutWireCube(10.0f);         // 원점에 그려지지만, 위에서 이동했으므로 (0, 10, 0)에 위치

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
    glutCreateWindow("Space + Axis + Cube");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}