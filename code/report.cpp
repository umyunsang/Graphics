// 3D 토러스(Torus, 도넛 모양) 그리기 - 점, 선, 점선, 색상을 모두 활용
// - 점(GL_POINTS): 토러스 중심축의 주요 지점들
// - 선(GL_LINE_STRIP): 토러스의 곡선 윤곽
// - 점선(GL_LINE_STIPPLE): 토러스 내부의 가이드 라인
// - 색상: 그라데이션 효과 (빨강->노랑->초록->파랑)
//
// [토러스 방정식 (Torus Equation)]
// 토러스는 원을 또 다른 원 주위로 회전시켜 만든 3차원 곡면입니다.
//
// 매개변수 방정식:
// x(θ, φ) = (R + r·cos(φ)) · cos(θ)
// y(θ, φ) = r · sin(φ)
// z(θ, φ) = (R + r·cos(φ)) · sin(θ)
//
// 여기서:
// - R: 큰 반지름 (major radius) - 토러스 중심에서 튜브 중심까지의 거리
// - r: 작은 반지름 (minor radius) - 튜브의 두께 반지름
// - θ: 큰 원의 각도 파라미터 (0 ≤ θ ≤ 2π)
// - φ: 작은 원(튜브 단면)의 각도 파라미터 (0 ≤ φ ≤ 2π)
//
// [참고 문헌]
// - Weisstein, Eric W. "Torus." From MathWorld--A Wolfram Web Resource.
//   https://mathworld.wolfram.com/Torus.html
// - OpenGL Programming Guide (Red Book), Chapter 2: State Management and Drawing Geometric Objects
// - 3D Computer Graphics: A Mathematical Introduction with OpenGL, Samuel R. Buss

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>

void RenderScene(void) {
    GLfloat x, y, z, angle, phi;
    GLfloat R = 50.0f;  // 토러스의 큰 반지름 (중심에서 튜브 중심까지)
    GLfloat r = 20.0f;  // 토러스의 작은 반지름 (튜브 두께)

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // 3D 효과를 위한 회전
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  // X축 기준 회전
    glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);  // Y축 기준 회전

    // ===== 1. 선(GL_LINE_STRIP): 토러스 외곽선 여러 개 그리기 =====
    // 토러스를 여러 원형 단면으로 표현
    glLineWidth(2.0f);

    for (int i = 0; i < 16; i++) {
        angle = (i * 2.0f * M_PI) / 16.0f;  // 큰 원을 16등분

        // 그라데이션 색상
        GLfloat colorFactor = (GLfloat)i / 16.0f;
        glColor3f(1.0f - colorFactor, colorFactor, 0.5f);

        glBegin(GL_LINE_LOOP);
        for (phi = 0.0f; phi <= 2.0f * M_PI; phi += 0.1f) {
            // 토러스 방정식:
            // x = (R + r*cos(phi)) * cos(angle)
            // y = r * sin(phi)
            // z = (R + r*cos(phi)) * sin(angle)
            x = (R + r * cos(phi)) * cos(angle);
            y = r * sin(phi);
            z = (R + r * cos(phi)) * sin(angle);

            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // ===== 2. 선(GL_LINE_STRIP): 토러스 둘레 방향 원형 라인 =====
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
    glLineWidth(3.0f);

    for (int j = 0; j < 8; j++) {
        phi = (j * 2.0f * M_PI) / 8.0f;

        glBegin(GL_LINE_LOOP);
        for (angle = 0.0f; angle <= 2.0f * M_PI; angle += 0.1f) {
            x = (R + r * cos(phi)) * cos(angle);
            y = r * sin(phi);
            z = (R + r * cos(phi)) * sin(angle);

            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // ===== 3. 점선(GL_LINE_STIPPLE): 중심축 가이드 라인 =====
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0x3333);  // 패턴
    glColor3f(0.0f, 1.0f, 1.0f);  // 하늘색
    glLineWidth(2.0f);

    // 중심 원 (토러스의 중심축)
    glBegin(GL_LINE_LOOP);
    for (angle = 0.0f; angle <= 2.0f * M_PI; angle += 0.1f) {
        x = R * cos(angle);
        y = 0.0f;
        z = R * sin(angle);
        glVertex3f(x, y, z);
    }
    glEnd();

    // 중심을 통과하는 십자 가이드 라인
    glBegin(GL_LINES);
    glVertex3f(-R, 0.0f, 0.0f);
    glVertex3f(R, 0.0f, 0.0f);

    glVertex3f(0.0f, -r, 0.0f);
    glVertex3f(0.0f, r, 0.0f);

    glVertex3f(0.0f, 0.0f, -R);
    glVertex3f(0.0f, 0.0f, R);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    // ===== 4. 점(GL_POINTS): 토러스의 주요 지점 강조 =====
    glColor3f(1.0f, 1.0f, 0.0f); 
    glPointSize(8.0f);

    glBegin(GL_POINTS);
    // 중심축의 4개 주요 지점
    for (int i = 0; i < 4; i++) {
        angle = (i * 2.0f * M_PI) / 4.0f;
        x = R * cos(angle);
        z = R * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    // ===== 추가: 토러스 최외곽과 최내곽 지점 강조 =====
    glColor3f(1.0f, 0.0f, 1.0f);  
    glPointSize(10.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < 8; i++) {
        angle = (i * 2.0f * M_PI) / 8.0f;
        // 최외곽 지점
        x = (R + r) * cos(angle);
        z = (R + r) * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    // 중심점
    glColor3f(1.0f, 1.0f, 1.0f);  // 흰색
    glPointSize(12.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();
    glFlush();
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLint wSize = 120;
    GLfloat aspectRatio;

    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -300, 300);
    } else {
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -300, 300);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("3D Torus - 점/선/점선/색상 활용");

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
