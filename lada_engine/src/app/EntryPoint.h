#pragma once
#include "Application.h"

namespace Lada {
    template<typename T>
    extern App::Application<T>* CreateApplication();
}

int main(int argc, char** argv);
