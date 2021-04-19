#include "vrpch.h"
#include "windowsWindow.h"
#include "Variant/Events/keyEvent.h"
#include "Variant/Events/ApplicationEvent.h"

namespace Variant {
	void windowsWindow::isVsync()
	{
		if (m_data.Vsync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}
	windowsWindow::windowsWindow()
	{
		init();
		setVsync(true);
	}

	windowsWindow::~windowsWindow()
	{
		glfwDestroyWindow(m_window);
	}

	unsigned int windowsWindow::getwidth()
	{
		return m_data.width;
	}

	unsigned int windowsWindow::getheight()
	{
		return m_data.height;
	}

	void windowsWindow::setVsync(bool isOn)
	{
		m_data.Vsync = isOn;
		isVsync();
	}

	void windowsWindow::setEventCallBack(windowCallFn callback)
	{
		m_data.callback = callback;
	}

	 Window* Window::create()
	{
		return new windowsWindow;
	}
	void windowsWindow::init(windowProps& props)
	{
		m_data.height = props.height;
		m_data.width = props.width;
		m_data.name = props.name;

		if (!glfwInit())
		{
			VR_core_error("GLFW initialization failed!!");
		}

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.name.c_str(), NULL, NULL);
		if (!m_window)
		{
			VR_core_error("Window initialization failed!!");
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSwapInterval(1);
		VR_core_info("Window started!!");

		
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS :
					{
						keyPressedEvent event(key, 0);
						data.callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						keyPressedEvent event(key, 0);
						data.callback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						keyPressedEvent event(key, 1);
						data.callback(event);
						break;
					}
				}
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) 
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callback(event);
			});
	}
	void windowsWindow::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}