#include "vrpch.h"
#include "Application.h"


namespace Variant {

	Application::Application()
	{
		m_Window = (std::unique_ptr<Window>)Window::create();
	}

	Application::~Application()
	{

	}


	void Application::run()
	{
		while (true)
		{
			m_Window->update();
		}
	}

}

