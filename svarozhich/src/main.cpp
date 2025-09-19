
#include <QApplication>

#include "MainWindow.h"

// +----------------------------------------------------------------------------------+
// | [Меню: File | Edit | View | Build | Window | Help]    [Play] [Pause] [Stop]      |
// +----------------------------------------------------------------------------------+
// | [Toolbar: Snap ▼ | Move/Rotate/Scale | Local/World | Grid On | Shading ▼ | ... ] |
// +------------------------+------------------------------------+--------------------+
// | Scene Hierarchy        |              Viewport               | Inspector          |
// |  (дерево)              |  (рендер из Lada / Gizmo)          | (компоненты ECS)   |
// |                        |                                     |                    |
// |                        |                                     |                    |
// +------------------------+--------------------+----------------+--------------------+
// | Console / Log          | Content Browser (Assets)                                |
// +----------------------------------------------------------------------------------+
// | Status bar: FPS | GPU time | Mem | Active tool | Project path                    |
// +----------------------------------------------------------------------------------+

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.showFullScreen();

    return app.exec();
}
