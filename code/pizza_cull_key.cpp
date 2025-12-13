// ----------------------------
// 학습 주제: 피자 원 그리기 (양면) + 후면 제거 + 키보드 상호작용
// ★★★ 시험 핵심 문제 (중요) ★★★
//
// 핵심 개념:
// 1. GL_TRIANGLE_FAN: 부채꼴 모양으로 원 그리기
// 2. 후면 제거 (Backface Culling):
//    - glEnable(GL_CULL_FACE): 후면 제거 활성화
//    - 반시계 방향(CCW)이 앞면, 시계 방향(CW)이 뒷면
//    - 뒷면은 렌더링되지 않음 (성능 향상)
// 3. 상호작용 (Callback Functions):
//    - glutKeyboardFunc: 일반 키 (a,d,w,x) -> 이동
//    - glutSpecialFunc: 특수 키 (방향키) -> 회전
//    - glutPostRedisplay(): 화면 갱신 요청 (필수!)
// ----------------------------

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

GLboolean bCull = GL_TRUE;   // 후면 제거 활성화 여부
GLfloat xTran = 0.0f;        // x축 이동량
GLfloat yTran = 0.0f;        // y축 이동량
GLfloat xRot = 0.0f;         // x축 회전각
GLfloat yRot = 0.0f;         // y축 회전각

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 후면 제거 기능 활성화 (뒷면은 그리지 않음)
    glEnable(GL_CULL_FACE);
    // 기본적으로 CCW(반시계)가 앞면, CW(시계)가 뒷면으로 정의됨

    glPushMatrix();
    // 변환 순서: 이동 -> 회전 (코드상 역순 적용: 회전 적용 후 이동 적용 의미)
    // OpenGL 행렬 곱셈은 역순으로 생각하는 것이 좋음
    // 여기서는 Local 좌표계 기준으로: 회전 후 이동
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(xTran, yTran, 0.0f);

    GLfloat angle, x, y;
    int count = 0;

    // 1. 앞면 그리기 (반시계 방향 - CCW)
    // 카메라가 정면에서 볼 때 보임
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);  // 중심점

        // 반시계 방향으로 돌며 정점 생성
        for (angle = 0.0f; angle <= 2.0f * PI + 0.01f; angle += PI / 8.0f) {
            // 색상 교차 (피자 조각 효과)
            if (count % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f); // 빨강
            else                glColor3f(0.0f, 1.0f, 0.0f); // 초록

            x = 50.0f * cos(angle);
            y = 50.0f * sin(angle);
            glVertex2f(x, y);
            count++;
        }
    glEnd();

    // 2. 뒷면 그리기 (시계 방향 - CW)
    // 회전해서 뒷면을 볼 때 보임 (파랑/노랑)
    // 후면 제거가 켜져 있어도, 카메라가 뒤로 돌아가면 이 면이 '앞'이 됨
    count = 0;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);

        // 시계 방향으로 돌며 정점 생성 (중요!)
        for (angle = 2.0f * PI; angle >= -0.01f; angle -= PI / 8.0f) {
            if (count % 2 == 0) glColor3f(0.0f, 0.0f, 1.0f); // 파랑
            else                glColor3f(1.0f, 1.0f, 0.0f); // 노랑

            x = 50.0f * cos(angle);
            y = 50.0f * sin(angle);
            glVertex2f(x, y);
            count++;
        }
    glEnd();

    glPopMatrix();
    glFlush();
}

// 특수 키(방향키) 처리 - 회전
void SpecialKeys(int key, int x, int y) {
    if(key == GLUT_KEY_UP)    xRot -= 5.0f;
    if(key == GLUT_KEY_DOWN)  xRot += 5.0f;
    if(key == GLUT_KEY_LEFT)  yRot -= 5.0f;
    if(key == GLUT_KEY_RIGHT) yRot += 5.0f;

    // 각도 제한
    if(xRot > 360.0f) xRot = 0.0f;
    if(xRot < -360.0f) xRot = 0.0f;
    if(yRot > 360.0f) yRot = 0.0f;
    if(yRot < -360.0f) yRot = 0.0f;

    glutPostRedisplay(); // 화면 갱신 요청
}

// 일반 키보드 처리 - 이동
void Keyboard(unsigned char key, int x, int y) {
    if(key == 'a')      xTran -= 2.0f; // 왼쪽
    else if(key == 'd') xTran += 2.0f; // 오른쪽
    else if(key == 'w') yTran += 2.0f; // 위
    else if(key == 'x') yTran -= 2.0f; // 아래 (s키 대신 x 사용함에 유의)

    glutPostRedisplay(); // 화면 갱신 요청
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
    glutCreateWindow("Interactive Pizza Circle (Cull Face)");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);      // 일반 키 등록
    glutSpecialFunc(SpecialKeys);    // 특수 키 등록

    std::cout << "★ 시험 핵심: 후면 제거 및 상호작용 ★" << std::endl;
    std::cout << "이동: a, d, w, x" << std::endl;
    std::cout << "회전: 방향키" << std::endl;

    glutMainLoop();
    return 0;
}