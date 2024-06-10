#include <iostream>
#include <windows.h>
#include <mutex>
#include "Log.h"

HANDLE Log::hWrite_ = INVALID_HANDLE_VALUE;
std::mutex Log::mutex_;

void Log::Initialize(HANDLE hWrite)
{
	std::lock_guard<std::mutex> lock(mutex_);
	hWrite_ = hWrite;
}

// 로그 레벨 선택 로그
void Log::Message(const std::string& message, LogLevel level)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (hWrite_ != INVALID_HANDLE_VALUE) {
        std::string coloredMessage = "[" + LogLevelToString(level) + "] " + message;
        DWORD written;
        WriteFile(hWrite_, coloredMessage.c_str(), static_cast<DWORD>(coloredMessage.size()), &written, nullptr);
        WriteFile(hWrite_, "\n", 1, &written, nullptr);
    }
}

// 일반 로그
void Log::LogMessage(const std::string& message)
{
    Message(message, LogLevel::LOG);
}

// 에러 로그
void Log::Error(const std::string& message)
{
    Message(message, LogLevel::LOGERROR);
}

// 성공 로그
void Log::Complete(const std::string& message)
{
    Message(message, LogLevel::COMPLETE);
}

// 경고 로그
void Log::Warnning(const std::string& message)
{
    Message(message, LogLevel::WARNING);
}

std::string Log::LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case LOG:
        return "LOG";
    case LOGERROR:
        return "ERROR";
    case COMPLETE:
        return "COMPLETE";
    case WARNING:
        return "WARNING";
    }
}
