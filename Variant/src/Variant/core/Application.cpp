#include "vrpch.h"
#include "Application.h"
#include "input.h"
#include "Variant/Renderer/Renderer.h"
#include "Variant/Renderer/RendererCommand.h"

namespace Variant {
	Application* Application::m_instance = NULL;
	Application::Application()
		:m_running(true)
	{
		m_instance = this;
		m_Window = (std::unique_ptr<Window>)Window::create();
		m_Window->setEventCallBack(std::bind(&Application::OnEvent,this ,std::placeholders::_1));

		ImLayer = std::make_unique<imguiLayer>();

	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		
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
			float prev=m_currTime;
			m_currTime=glfwGetTime();
			deltaTime dt = m_currTime - prev;

			for (layer* layer : m_layerstack)
			{
				layer->OnUpdate(dt);
			}

			ImLayer->Begin();
			for (layer* layer : m_layerstack)
				layer->OnImGuiRender();
			ImLayer->OnImGuiRender();
			ImLayer->End();

			m_Window->update();
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		//RendererCommand::setViewPort(e.GetWidth(), e.GetHeight());
		return false;
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

