#include <LADA.h>

#include "DemoApp.h"

namespace lada {
    app::Application* CreateApplication() {
        return new DemoApp();
    }
}
