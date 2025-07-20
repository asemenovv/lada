#include <LADA.h>

#include "DemoApp.h"

namespace Lada {
    App::Application* CreateApplication() {
        return new DemoApp();
    }
}
