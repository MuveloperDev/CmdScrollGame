#include <string>
#include <mutex>
#include <windows.h>
#pragma once
enum LogLevel {
    LOG = 7,        // ���
    LOGERROR = 4,   // ������
    COMPLETE = 2,   // ���
    WARNING = 6     // �����
};
class Log
{
public:
    static void Initialize(HANDLE hWrite);
    static void Message(const std::string& message, LogLevel level);
    static void LogMessage(const std::string& message);
    static void Error(const std::string& message);
    static void Complete(const std::string& message);
    static void Warnning(const std::string& message);

public:
    static void Cout(const std::string& message);
    
private:

    static std::string LogLevelToString(LogLevel level);
    static HANDLE hWrite_;
    static std::mutex mutex_;
};

