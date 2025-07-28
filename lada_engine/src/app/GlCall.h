#pragma once

#include <csignal>

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GL_CALL(x) Logger::GLClearError();\
x;\
ASSERT(Logger::GLLogCall(#x, __FILE__, __LINE__))

namespace Lada::Logger {
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, const int line);
}
