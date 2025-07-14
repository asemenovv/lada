#include "EntryPoint.h"

#include "Log.h"

int main(int argc, char** argv) {
    lada::log::Log::Init();
    LD_CORE_WARN("Logging is initialized");
    int a = 42;
    LD_INFO("Hello! Var={0}", a);

    const auto app = lada::CreateApplication();
    app->Run();
    delete app;
}
