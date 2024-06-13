// LogSystem.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>

enum LogLevel {
    LOG = 7,        // 흰색
    LOGERROR = 4,      // 빨간색
    COMPLETE = 2,   // 녹색
    WARNING = 6     // 노란색
};
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
LogLevel StringToLogLevel(std::string str)
{
    if (str == "LOG") return LogLevel::LOG;
    else if (str == "WARNING") return LogLevel::WARNING;
    else if (str == "COMPLETE") return LogLevel::COMPLETE;
    else return LogLevel::LOGERROR;
}

std::string GetCurrentDateTime(bool isLog = false) {
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    char buffer[80];
    const char* type = isLog == true ? "%Y-%m-%d_%H:%M:%S" : "%Y-%m-%d_%H-%M-%S";
    strftime(buffer, sizeof(buffer), type, &localTime);
    return std::string(buffer);
}

bool CreateDirectoryIfNotExists(const std::string& path) {
    DWORD attribs = GetFileAttributesA(path.c_str());
    if (attribs == INVALID_FILE_ATTRIBUTES || !(attribs & FILE_ATTRIBUTE_DIRECTORY)) {
        return CreateDirectoryA(path.c_str(), nullptr);
    }
    return true;
}

int main()
{
    std::string logDirectory = "E:/Work/TEST/CMD_ScrollGame/CmdScrollGame/ScrollGame/Logs/";
    if (!CreateDirectoryIfNotExists(logDirectory)) {
        std::cerr << "Failed to create log directory: " << logDirectory << std::endl;
        return 1;
    }
    std::string logFileName = "[ " + GetCurrentDateTime() + " ]_Log.txt";
    std::string logFilePath = logDirectory + logFileName;
    std::cout << logFilePath << std::endl;
    std::ofstream logFile(logFilePath, std::ios::out); // 새 로그 파일 생성

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
        return 1;
    }


    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.length() > 3 && line[0] == '[') 
        {
            size_t endPos = line.find(']');
            if (endPos != std::string::npos) {
                LogLevel level = StringToLogLevel(line.substr(1, endPos - 1));
                int color = level;
                std::string levelStr = line.substr(1, endPos - 1);
                setColor(color);
                //line = line.substr(endPos + 2); // 색상 코드와 공백 제거
            }
        }
        std::cout << " [ " + GetCurrentDateTime(true) + " ] " + line << std::endl;
        logFile << " [ " + GetCurrentDateTime(true) + " ] " + line << std::endl; // 파일에 로그 기록
        setColor(LOG); // 기본 색상으로 복원
    }
    logFile.close();
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
