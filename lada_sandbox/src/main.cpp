#include <LADA.h>

#include "DemoApp.h"

namespace Lada {
    App::Application<Context>* CreateApplication() {
        return new DemoApp();
    }
}
