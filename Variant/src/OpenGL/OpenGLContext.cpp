#include "vrpch.h"
#include "OpenGLContext.h"
#include "Variant/core/core.h"
#include "Variant/core/log.h"
#include "glad/glad.h"

namespace Variant {
	OpenGLContext::OpenGLContext(void* window)
	{
		m_window = static_cast<GLFWwindow*>(window);
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_window);
		VR_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

		glfwSwapInterval(1);
		VR_core_info("Window started!!");
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}