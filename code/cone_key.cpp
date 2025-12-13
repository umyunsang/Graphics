// ----------------------------
// 학습 주제: 원뿔 그리기 (Cone) + 키보드 회전
// 핵심 개념:
// 1. 3D 입체 도형 구성:
//    - 옆면: GL_TRIANGLE_FAN (꼭지점 1개 + 밑면 원주 점들)
//    - 밑면: GL_TRIANGLE_FAN (밑면 중심점 1개 + 밑면 원주 점들)
// 2. 3D 투영: gluPerspective 사용
// 3. 카메라 이동: glTranslatef(0, 0, -dist)로 물체를 뒤로 밀어서 봄
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

void RenderScene(void) {
    // 깊이 버퍼와 컬러 버퍼를 모두 초기화 (3D 렌더링 필수)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 여기서는 깊이 버퍼가 없어서 그냥 컬러만 해도 되지만 습관적으로

    glEnable(GL_CULL_FACE); // 후면 제거

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    GLfloat angle, x, y;
    GLfloat radius = 50.0f;
    GLfloat height = 80.0f;
    int segments = 16;

    // 1. 원뿔 옆면 그리기
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, height); // 꼭지점 (Z = height)

        // 반시계 방향으로 원주 점 생성
        for (int i = 0; i <= segments; i++) {
            angle = 2.0f * PI * i / segments;
            x = radius * cos(angle);
            y = radius * sin(angle);

            if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else            glColor3f(0.0f, 1.0f, 0.0f);

            glVertex3f(x, y, 0.0f); // 밑면의 Z = 0
        }
    glEnd();

    // 2. 원뿔 밑면 그리기
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f); // 밑면 중심

        // 시계 방향으로 원주 점 생성 (밑에서 봤을 때 앞면이 되도록)
        for (int i = 0; i <= segments; i++) {
            angle = 2.0f * PI * i / segments;
            x = radius * cos(angle);
            y = radius * sin(angle);

            if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else            glColor3f(0.0f, 1.0f, 0.0f);

            // y축 반전하여 시계 방향 생성 효과
            glVertex3f(x, -y, 0.0f);
        }
    glEnd();

    glPopMatrix();
    glutSwapBuffers(); // 더블 버퍼링 사용 시 SwapBuffers
}

void SpecialKeys(int key, int x, int y) {
    if(key == GLUT_KEY_UP)    xRot -= 5.0f;
    if(key == GLUT_KEY_DOWN)  xRot += 5.0f;
    if(key == GLUT_KEY_LEFT)  yRot -= 5.0f;
    if(key == GLUT_KEY_RIGHT) yRot += 5.0f;

    if(xRot > 360.0f) xRot = 0.0f;
    if(xRot < -360.0f) xRot = 0.0f;
    if(yRot > 360.0f) yRot = 0.0f;
    if(yRot < -360.0f) yRot = 0.0f;

    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    
    // 원근 투영 (Perspective Projection)
    gluPerspective(45.0f, aspectRatio, 1.0f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // 카메라 위치: Z축 뒤로 물러남
    glTranslatef(0.0f, -30.0f, -250.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 더블 버퍼링
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Cone Interactive");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);

    std::cout << "Rotate with Arrow Keys" << std::endl;

    glutMainLoop();
    return 0;
}