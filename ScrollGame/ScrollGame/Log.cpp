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

// �α� ���� ���� �α�
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

// �Ϲ� �α�
void Log::LogMessage(const std::string& message)
{
    Message(message, LogLevel::LOG);
}

// ���� �α�
void Log::Error(const std::string& message)
{
    Message(message, LogLevel::LOGERROR);
}

// ���� �α�
void Log::Complete(const std::string& message)
{
    Message(message, LogLevel::COMPLETE);
}

// ��� �α�
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
