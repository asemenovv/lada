#include "EntryPoint.h"

int main(int argc, char** argv) {
    const auto app = lada::CreateApplication();
    app->Run();
    delete app;
}
