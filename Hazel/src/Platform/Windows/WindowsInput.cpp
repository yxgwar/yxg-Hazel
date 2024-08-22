#include "hzpch.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel {
	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> Input::GetMousePos()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePos();
		return x;
	}
	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePos();
		return y;
	}
}