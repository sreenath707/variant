#pragma once
#include "core.h"
#include "Window.h"
#include "layerStack.h"


namespace Variant {

	class VR_API Application
	{
		bool m_running;
		std::unique_ptr<Window> m_Window;
		layerStack m_layerstack;
		
	public:
		Application();

		virtual ~Application();

		void run();
		void OnEvent(Event& e);
		bool OnWindowClose(Event& e);
		void pushLayer(layer* layer);
		void popLayer(layer* layer);

	};

	Application* CreateApplication();

}
