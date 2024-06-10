﻿// ScrollGame.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include "Example.h"
#include "Log.h"
#include "Util.h"

int main()
{
    // 파이프 생성
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
    HANDLE hRead, hWrite;
    CreatePipe(&hRead, &hWrite, &sa, 0);
    SetHandleInformation(hWrite, HANDLE_FLAG_INHERIT, 0);

    // 로그 프로세스 생성
    STARTUPINFOW si = { sizeof(STARTUPINFOW) };  // STARTUPINFO를 STARTUPINFOW로 변경
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); // ZeroMemory 사용으로 구조체 초기화
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = hRead;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 유니코드 문자열로 변환
    wchar_t command[] = L"E:/Work/TEST/CMD_ScrollGame/CmdScrollGame/ScrollGame/build/LogSystem/Debug/LogSystem.exe";

    // 유니코드 버전의 CreateProcess 함수 사용
    if (!CreateProcessW(
        nullptr,
        command,
        nullptr,
        nullptr,
        TRUE,
        CREATE_NEW_CONSOLE,
        nullptr,
        nullptr,
        &si,
        &pi
    )) {
        // 오류 처리
        DWORD error = GetLastError();
        std::wcerr << L"CreateProcessW failed with error " << error << std::endl;
        return 1;
    }

    CloseHandle(hRead);
    Log::Initialize(hWrite);

    // 로그 메시지 전송
    Log::Complete("[ Launch Application ]");

    // 메인 프로그램 로직
    // 예제: 싱글턴 사용
    // ...
    // 
    // MySingleton& instance1 = MySingleton::getInstance();
    // instance1.doSomething();
    // ...
    Util& utilInstance = Util::GetInstance();
    while (true)
    {
        SHORT lefttState = GetAsyncKeyState(VK_LEFT);
        SHORT rightState = GetAsyncKeyState(VK_RIGHT);

        bool isLeft = (lefttState & 0x8000) != 0;
        bool isRight = (rightState & 0x8000) != 0;

        if (isLeft)
        {
            break;
        }

        if (isRight)
        {
            utilInstance.Clear();
            Log::LogMessage("Regular log message");
            Log::Error("log error");
            Log::Complete("log Complete");
            Log::Warnning("log Warnning");
        }
    }

    Example& instance = Example::GetInstance();
    instance.DoSomthing();
    // 프로세스 종료
    CloseHandle(hWrite);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

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
