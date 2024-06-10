@echo off
set BUILD_DIR=build

:: 빌드 디렉토리 삭제 및 재생성
if exist %BUILD_DIR% (
    rmdir /s /q %BUILD_DIR%
)
mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: CMake 구성 및 빌드
cmake ..
cmake --build .

:: 실행 파일 위치
set SCROLLGAME_EXECUTABLE=%cd%\ScrollGame\Debug\ScrollGame.exe

:: 빌드가 성공적으로 완료되었는지 확인
if exist "%SCROLLGAME_EXECUTABLE%" (
    echo Running ScrollGame...
    "%SCROLLGAME_EXECUTABLE%"
) else (
    echo Build failed or executable not found.
)
pause