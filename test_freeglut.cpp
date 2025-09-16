#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

// 윈도우 크기
int windowWidth = 800;
int windowHeight = 600;

// 회전 각도
float rotationAngle = 0.0f;

// 초기화 함수
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검은색 배경
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // 조명 설정
    GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    
    // 재질 설정
    GLfloat materialColor[] = {0.2f, 0.6f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
}

// 디스플레이 함수
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // 카메라 위치
              0.0, 0.0, 0.0,  // 시선 방향
              0.0, 1.0, 0.0); // 업 벡터
    
    // 회전 적용
    glRotatef(rotationAngle, 1.0f, 1.0f, 0.0f);
    
    // 큐브 그리기
    glutSolidCube(1.0);
    
    glutSwapBuffers();
}

// 타이머 함수 (애니메이션용)
void timer(int value) {
    rotationAngle += 2.0f;
    if (rotationAngle >= 360.0f) {
        rotationAngle = 0.0f;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 약 60 FPS
}

// 리셰이프 함수
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// 키보드 입력 처리
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC 키
        case 'q':
        case 'Q':
            std::cout << "프로그램을 종료합니다." << std::endl;
            exit(0);
            break;
        case 'r':
        case 'R':
            rotationAngle = 0.0f;
            std::cout << "회전을 리셋했습니다." << std::endl;
            break;
    }
}

// 마우스 클릭 처리
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "마우스 왼쪽 버튼 클릭: (" << x << ", " << y << ")" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "FreeGLUT 테스트 프로그램을 시작합니다." << std::endl;
    std::cout << "키보드 조작:" << std::endl;
    std::cout << "  ESC, Q: 프로그램 종료" << std::endl;
    std::cout << "  R: 회전 리셋" << std::endl;
    std::cout << "  마우스 왼쪽 클릭: 좌표 출력" << std::endl;
    
    // GLUT 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("FreeGLUT 테스트 - 회전하는 큐브");
    
    // 콜백 함수 등록
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, timer, 0);
    
    // OpenGL 초기화
    init();
    
    // 메인 루프 시작
    glutMainLoop();
    
    return 0;
}
