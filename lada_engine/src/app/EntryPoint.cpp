#include "ldpch.h"
#include "EntryPoint.h"

#include "Logger.h"

int main(int argc, char** argv) {
    Lada::Log::Logger::Init();
    const auto app = Lada::CreateApplication();
    app->Run();
    delete app;
}
