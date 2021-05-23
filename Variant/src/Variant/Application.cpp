#include "vrpch.h"
#include "Application.h"
#include "input.h"

namespace Variant {
	Application* Application::m_instance = NULL;
	Application::Application()
		:m_running(true)
	{
		m_instance = this;
		m_Window = (std::unique_ptr<Window>)Window::create();
		m_Window->setEventCallBack(std::bind(&Application::OnEvent,this ,std::placeholders::_1));

	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		VR_core_info(e.ToString());
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_layerstack.rbegin(); it != m_layerstack.rend(); ++it)
		{
			if (e.isHandled)
			{
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::run()
	{
		while (m_running)
		{
			
			for (layer* layer : m_layerstack)
			{
				layer->OnUpdate();
			}
			m_Window->update();
			glClearColor(0, 0, 0.7f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_running = false;
		return true;
	}

	void Application::pushLayer(layer* layer)
	{
		m_layerstack.pushLayer(layer);
		layer->OnAttach();
	}

	void Application::popLayer(layer* layer)
	{
		m_layerstack.popLayer(layer);
	}

	void Application::pushOverlay(layer* layer)
	{
		m_layerstack.pushOverlay(layer);
		layer->OnAttach();
	}

	void Application::popOverlay(layer* layer)
	{
		m_layerstack.popOverlay(layer);
	}

}

