#include "vrpch.h"
#include "Application.h"


namespace Variant {

	Application::Application()
		:m_running(true)
	{
		m_Window = (std::unique_ptr<Window>)Window::create();
		m_Window->setEventCallBack(std::bind(&Application::OnEvent,this ,std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		std::cout << e << std::endl;
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	}

	void Application::run()
	{
		while (m_running)
		{
			m_Window->update();
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_running = false;
		return true;
	}

}

