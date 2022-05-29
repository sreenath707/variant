#pragma once
#include "Variant/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Variant {

	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_window;
	public:
		OpenGLContext(void* window);
		virtual void init()override;
		virtual void swapBuffers()override;
	};
}
