// ----------------------------
// 학습 주제: 카메라 변환 공간 + 좌표 축 그리기
// 핵심 개념:
// 1. 카메라 변환 (View Transformation):
//    - 세상의 물체를 카메라 기준으로 옮기는 것과 같음
//    - OpenGL에서는 카메라를 고정하고 세상을 반대로 움직이는 방식을 사용
//    - 예: 카메라를 뒤로 10 이동 == 물체를 앞으로 10 이동
// 2. 좌표 축 그리기: X(Red), Y(Green), Z(Blue)
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

    glLoadIdentity(); // 1. 단위 행렬로 초기화

    // 2. 카메라 변환 적용
    // 우리는 카메라를 (0, 0, 30)에 놓고 원점을 바라보고 싶음.
    // OpenGL에서는 세상을 반대로 이동시켜야 함.
    // -> Z축으로 -30 이동 (glTranslatef(0,0,-30))
    // 그 다음 회전 적용
    glTranslatef(0.0f, 0.0f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);   // X축 기준 30도 회전
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);  // Y축 기준 -30도 회전

    // 3. 변환된 좌표계 위에 축 그리기
    // 이 축들은 위에서 적용한 변환(카메라 뷰)에 의해 회전되어 보임
    glBegin(GL_LINES);
        // X축 (빨간색)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);

        // Y축 (녹색)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 10.0f, 0.0f);

        // Z축 (파란색)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    glFlush();
}

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat aspectRatio;
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    aspectRatio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, aspectRatio, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Camera Space Transformation");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}