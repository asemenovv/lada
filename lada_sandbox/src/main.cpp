#include "DemoApp.h"

int main() {
    const auto demo = new DemoApp();
    demo->Run();
    delete demo;
}
