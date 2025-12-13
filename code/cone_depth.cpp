// ----------------------------
// 학습 주제: 원뿔 그리기 + 깊이 테스트 (Depth Test)
// 핵심 개념:
// 1. 깊이 버퍼 (Depth Buffer):
//    - 각 픽셀의 깊이(z값)를 저장하는 메모리 공간
//    - 가려진 면을 자동으로 제거하기 위해 사용
// 2. GL_DEPTH_TEST:
//    - 활성화 시, 새로 그려질 픽셀의 z값과 기존 z값을 비교
//    - 더 가까운(깊이 값이 작은) 픽셀만 그림
// 3. GLUT_DEPTH: 윈도우 생성 시 깊이 버퍼 할당
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
GLboolean bDepth = GL_TRUE;  // 깊이 테스트 on/off 상태

void RenderScene(void) {
    // 컬러 버퍼와 깊이 버퍼를 모두 클리어 (매 프레임 필수)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 깊이 테스트 설정
    if (bDepth) glEnable(GL_DEPTH_TEST);
    else        glDisable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);   // 후면 제거 활성화

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    GLfloat angle, x, y;
    GLfloat radius = 50.0f;
    GLfloat height = 80.0f;
    int segments = 16;
    int count = 0;

    // 1. 원뿔 옆면 (GL_TRIANGLE_FAN)
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, height);  // 꼭지점

        for (int i = 0; i <= segments; i++) {
            angle = 2.0f * PI * i / segments;
            x = radius * cos(angle);
            y = radius * sin(angle);
            
            if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else            glColor3f(0.0f, 1.0f, 0.0f);

            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    // 2. 원뿔 밑면 (GL_TRIANGLE_FAN)
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);  // 중심점

        // 시계 방향으로 원주 점 생성
        for (int i = 0; i <= segments; i++) {
            angle = 2.0f * PI * i / segments;
            x = radius * cos(angle);
            y = radius * sin(angle);

            if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else            glColor3f(0.0f, 1.0f, 0.0f);

            glVertex3f(x, -y, 0.0f);
        }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
    if (key == 'd' || key == 'D') {
        bDepth = !bDepth;  // 깊이 테스트 토글
        std::cout << "Depth Test: " << (bDepth ? "ON" : "OFF") << std::endl;
        glutPostRedisplay();
    }
}

void SpecialKeys(int key, int x, int y) {
    if(key == GLUT_KEY_UP)    xRot -= 5.0f;
    if(key == GLUT_KEY_DOWN)  xRot += 5.0f;
    if(key == GLUT_KEY_LEFT)  yRot -= 5.0f;
    if(key == GLUT_KEY_RIGHT) yRot += 5.0f;
    
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -30.0f, -250.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // GLUT_DEPTH 추가: 깊이 버퍼 할당 요청
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Cone with Depth Buffer");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeys);

    std::cout << "Press 'd' to toggle Depth Test" << std::endl;

    glutMainLoop();
    return 0;
}