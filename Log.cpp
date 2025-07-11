#include <iostream>

class Log {
public:
    enum Level
    {
        ErrorLevel = 0, WarnLevel, InfoLevel
    };
private:
    Level m_LogLevel = InfoLevel;
public:
    void SetLevel(const Level level) {
        m_LogLevel = level;
    }

    void Error(const char* message) {
        if (m_LogLevel >= ErrorLevel)
            std::cout << "[ERROR]: " << message << std::endl;
    }

    void Warn(const char* message) {
        if (m_LogLevel >= WarnLevel)
            std::cout << "[WARNING]: " << message << std::endl;
    }

    void Info(const char* message) {
        if (m_LogLevel >= InfoLevel)
            std::cout << "[INFO]: " << message << std::endl;
    }
};
