#include "DemoApp.h"

#include <string>

#include "RenderingLayer.h"
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
    PushLayer(new RenderingLayer());
}

void DemoApp::OnDebugUIRender(Lada::App::DebugUIManager* manager) {
    manager->Slider("Rotation", &m_R, 0.0f, 1.0f);
    const float timePerFrame = 1000.0f / manager->FrameRate();
    manager->Text("Application average %.3f ms/frame (%.1f FPS)", timePerFrame, manager->FrameRate());
}
