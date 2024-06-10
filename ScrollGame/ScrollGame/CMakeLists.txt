# ScrollGame 프로젝트 설정
project(ScrollGame)

# 모든 .cpp 파일을 자동으로 추가
file(GLOB SOURCES "*.cpp")

# 유니코드 모드 설정
add_definitions(-DUNICODE -D_UNICODE)

# 실행 파일 추가
add_executable(ScrollGame ${SOURCES})