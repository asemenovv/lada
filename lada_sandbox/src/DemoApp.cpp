#include "DemoApp.h"

#include <string>

#include "DemoImGuiLayer.h"
#include "RendererLayer.h"
#include "events/MouseEvent.h"

DemoApp::DemoApp(): Application("LADA Engine", 640, 480) {
    GetEventManager()->REGISTER_HANDLER(Lada::Event::WindowCloseEvent, {
        LD_TRACE("WindowCloseEvent is fired {}", event.ToString());
        return true;
        });
    GetEventManager()->REGISTER_HANDLER(Lada::Event::WindowResizeEvent, {
        LD_TRACE("WindowResizeEvent is fired {}", event.ToString());
        return true;
        });
    m_ImGuiLayer = new DemoImGuiLayer();
    PushLayer(new RendererLayer());
    PushLayer(m_ImGuiLayer);
}
