#include "vrpch.h"
#include "windowsInput.h"

namespace Variant {

    input* input::s_instance = new windowsInput;

    bool windowsInput::isKeyPressedImpl(int keycode)
    {
        GLFWwindow* m_window = Application::Get().GetWindow().getGlfwWindow();
        auto state = glfwGetKey(m_window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool windowsInput::isMouseButtonPressedImpl(int button)
    {
        GLFWwindow* m_window = Application::Get().GetWindow().getGlfwWindow();
        auto state = glfwGetMouseButton(m_window, button);
        return state == GLFW_PRESS;
    }

    float windowsInput::getMouseXPosImpl()
    {
        GLFWwindow* m_window = Application::Get().GetWindow().getGlfwWindow();
        double x_state,y_state;
        glfwGetCursorPos(m_window, &x_state, &y_state);
        return (float)x_state;
    }

    float windowsInput::getMouseYPosImpl()
    {

        GLFWwindow* m_window = Application::Get().GetWindow().getGlfwWindow();
        double x_state,y_state;
        glfwGetCursorPos(m_window, &x_state, &y_state);
        return (float)y_state;
    }

}
