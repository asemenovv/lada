#include "EntryPoint.h"

#include "Log.h"

int main(int argc, char** argv) {
    lada::log::Log::Init();
    const auto app = lada::CreateApplication();
    app->Run();
    delete app;
}
