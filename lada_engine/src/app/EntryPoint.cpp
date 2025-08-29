#include "ldpch.h"
#include "EntryPoint.h"

#include "Logger.h"

int main(int argc, char** argv) {
    // Disable MoltenVK logs
    setenv("MVK_CONFIG_LOG_LEVEL", "2", 1);
    Lada::Log::Logger::Init();
    const auto app = Lada::CreateApplication();
    app->Run();
    delete app;
}
