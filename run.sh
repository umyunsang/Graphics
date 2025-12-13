#!/bin/bash

# C++ 파일 자동 빌드 및 실행 스크립트
# 사용법: ./run_cpp.sh filename.cpp

if [ $# -eq 0 ]; then
    echo "Usage: ./run_cpp.sh filename.cpp"
    echo "Example: ./run_cpp.sh code/draw_square.cpp"
    exit 1
fi

CPP_FILE=$1
BASENAME=$(basename "$CPP_FILE" .cpp)
EXECUTABLE_NAME="build_$BASENAME"

echo "Compiling: $CPP_FILE"
echo "Executable: $EXECUTABLE_NAME"

# C++ 파일 컴파일
if g++ -o "$EXECUTABLE_NAME" "$CPP_FILE" -framework GLUT -framework OpenGL; then
    echo "Compile success!"
    echo "Running..."
    echo "----------------------------------------"
    
    # 실행
    ./"$EXECUTABLE_NAME"
    
    echo "----------------------------------------"
    echo "Program finished"
    
    # 실행파일 정리 (선택사항)
    read -p "Delete the executable? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        rm "$EXECUTABLE_NAME"
        echo "Executable deleted: $EXECUTABLE_NAME"
    fi
else
    echo "Compile failed!"
    exit 1
fi
