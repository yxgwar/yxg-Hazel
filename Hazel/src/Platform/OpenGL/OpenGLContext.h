#pragma once

#include "Hazel/Render/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {
	class OpenGLContext :public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
