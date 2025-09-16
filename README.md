# Graphics

이 레포지토리는 컴퓨터 그래픽스 학습을 위한 프로젝트들을 포함합니다.

## 프로젝트 목록

### FreeGLUT 테스트
- **파일**: `test_freeglut.cpp`
- **설명**: FreeGLUT 라이브러리를 사용한 3D 큐브 렌더링 테스트
- **기능**:
  - 회전하는 3D 큐브
  - 조명 효과
  - 마우스/키보드 상호작용
  - 애니메이션 (60 FPS)

## 빌드 및 실행

### macOS에서 FreeGLUT 테스트 실행

1. **의존성 설치**:
   ```bash
   brew install freeglut
   ```

2. **컴파일**:
   ```bash
   g++ -o test_freeglut test_freeglut.cpp -framework OpenGL -framework GLUT
   ```

3. **실행**:
   ```bash
   ./test_freeglut
   ```

## 조작법

- **ESC, Q**: 프로그램 종료
- **R**: 회전 리셋
- **마우스 왼쪽 클릭**: 좌표 출력

## 시스템 요구사항

- macOS (OpenGL 지원)
- Xcode Command Line Tools
- Homebrew (의존성 설치용)
