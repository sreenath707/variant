#include "vrpch.h"
#include "windowsWindow.h"

namespace Variant {

	windowsWindow::windowsWindow()
	{
		init();
	}

	windowsWindow::~windowsWindow()
	{
		glfwDestroyWindow(m_window);
	}

	unsigned int windowsWindow::getwidth()
	{
		return m_width;
	}

	unsigned int windowsWindow::getheight()
	{
		return m_height;
	}

	 Window* Window::create()
	{
		return new windowsWindow;
	}
	void windowsWindow::init(windowProps& props)
	{
		m_height = props.height;
		m_width = props.width;
		m_name = props.name;

		if (!glfwInit())
		{
			VR_core_error("GLFW initialization failed!!");
		}

		m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
		if (!m_window)
		{
			VR_core_error("Window initialization failed!!");
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);
		VR_core_info("Window started!!");

	}
	void windowsWindow::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}