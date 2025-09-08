#include "ldpch.h"
#include "Input.h"
#include "app/Application.h"
#include <GLFW/glfw3.h>

namespace Lada::Input {
    bool Input::IsKeyPressed(const KeyCode keycode) {
        auto* window = App::Application::Get().GetWindow().GetNativeWindow();
        const auto state = glfwGetKey(static_cast<GLFWwindow*>(window), keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(const MouseCode button) {
        auto* window = App::Application::Get().GetWindow().GetNativeWindow();
        const auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), button);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition() {
        auto* window = App::Application::Get().GetWindow().GetNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float Input::GetMouseX() {
        return GetMousePosition().x;
    }

    float Input::GetMouseY() {
        return GetMousePosition().y;
    }
}
