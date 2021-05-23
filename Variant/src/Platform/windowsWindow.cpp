#include "vrpch.h"
#include "windowsWindow.h"
#include "Variant/Events/keyEvent.h"
#include "Variant/Events/ApplicationEvent.h"
#include "Variant/Events/mouseEvent.h"


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
		VR_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
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
						keyReleaseEvent event(key);
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
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
				WindowResizeEvent event(width, height);
				data.callback(event);
			});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						mouseClickEvent event(button);
						data.callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						mouseReleaseEvent event(button);
						data.callback(event);
						break;
					}
				    
				}
				
			});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos,double yPos) 
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				mousePosEvent event(xPos, yPos);
				data.callback(event);
			});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) 
			{
				windowData data = *(windowData*)glfwGetWindowUserPointer(window);
				mouseScrollEvent event(xOffset, yOffset);
				data.callback(event);
			});
	}
	void windowsWindow::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}