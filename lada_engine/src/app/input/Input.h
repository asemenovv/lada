#pragma once
#include <glm/vec2.hpp>

#include "MouseCodes.h"
#include "KeyCodes.h"

namespace Lada::Input {
    class Input final {
    public:
        static bool IsKeyPressed(KeyCode keycode);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}
