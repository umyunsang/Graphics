#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>

void RenderScene(void) {
    std::cout << "RenderScene" << std::endl;

    glClear(GL_COLOR_BUFFER_BIT); // 현재 활성화된 버퍼(여기서는 컬러 버퍼)를 지움

    glFlush(); // OpenGL 명령을 즉시 실행하도록 강제함
}

void SetupRc(void)
{
    // std::cout << "SetupRc - 빨간색" << std::endl;
    // glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색 배경


    // std::cout << "SetupRc - 녹색" << std::endl;
    // glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 녹색 배경


    std::cout << "SetupRc - 노란색" << std::endl;
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // 노란색 배경
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); // GLUT 라이브러리 초기화 및 명령행 인자 처리
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 디스플레이 모드 설정: 단일 버퍼, RGB 컬러
    glutInitWindowSize(640, 480); // 윈도우 크기 설정 (가로 640, 세로 480)
    glutInitWindowPosition(100, 100); // 윈도우가 화면에 생성될 위치 지정 (좌상단 기준)
    glutCreateWindow("Hello World"); // 윈도우 생성 및 타이틀 지정
    
    
    SetupRc(); // 렌더링 상태 설정 함수 호출
    glutDisplayFunc(RenderScene); // 디스플레이 콜백 함수 등록 (화면이 다시 그려질 때 RenderScene 호출)
    
    glutMainLoop(); // 이벤트 루프 진입 (프로그램이 종료될 때까지 이벤트 처리)
    return 0;
}