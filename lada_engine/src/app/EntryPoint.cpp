#include "ldpch.h"
#include "EntryPoint.h"

#include "Logger.h"
#include "../../../lada_sandbox/src/DemoContext.h"

int main(int argc, char** argv) {
    Lada::Log::Logger::Init();
    const auto app = Lada::CreateApplication<Context>();
    app->Run();
    delete app;
}
